#include "ADNPYReader.h"

#include <iocsh.h>
#include <epicsExport.h>

static void acquire_thread_callback(void* drvPvt)    { ((ADNPYReader*) drvPvt)->acquireThread(); }

extern "C"
{
	void NPYConfig(const char* portname)
	{
		new ADNPYReader(portname);
	}
}

ADNPYReader::ADNPYReader(const char* portname) :
	ADDriver(portname,
	1,
	0,
	0,
	0,
	0,
	0,
	ASYN_CANBLOCK,
	1,
	0,
	0)
{
	this->addParam(ADNPY_FilePath, asynParamOctet);
	this->setStringParam(params[ADNPY_FilePath], "");
	
	this->setIntegerParam(ADStatus, ADStatusIdle);
	this->callParamCallbacks();
}

void ADNPYReader::addParam(const char* paramname, asynParamType type)
{
	int tempval;
	std::string key(paramname);
	
	createParam( paramname, type, &tempval);
	
	this->params[key] = tempval;
}


asynStatus ADNPYReader::writeInt32(asynUser* pasynUser, epicsInt32 value)
{
	int addr;
	int function;
	const char* paramName;
	
	int status = parseAsynUser(pasynUser, &function, &addr, &paramName);
	if (status != asynSuccess)    { return (asynStatus) status; }
	
	
	int adstatus;
	getIntegerParam(ADStatus, &adstatus);
	
	setIntegerParam(addr, function, value);
	
	if (function == ADAcquire)
	{	
		if (value == 1 && adstatus == ADStatusIdle)
		{
			this->setIntegerParam(ADStatus, ADStatusAcquire);
			this->callParamCallbacks();
		
			epicsThreadCreate("ADNPYReader::acquireThread()",
	                  epicsThreadPriorityLow,
	                  epicsThreadGetStackSize(epicsThreadStackMedium),
	                  (EPICSTHREADFUNC)::acquire_thread_callback,
	                  this);
		}
	}
	else
	{
		status = ADDriver::writeInt32(pasynUser, value);
	}
	
	callParamCallbacks(addr);
	return (asynStatus) status;
}


void ADNPYReader::acquireThread()
{
	std::string filepath;
		
	this->getStringParam(params[ADNPY_FilePath], filepath);
		
	printf("%s\n", filepath.c_str());
}



static const iocshArg NPYConfigArg0 = { "Port name", iocshArgString };

static const iocshArg * const NPYConfigArgs[] = { &NPYConfigArg0 };

static void configNPYCallFunc(const iocshArgBuf *args)
{
	NPYConfig(args[0].sval);
}

static const iocshFuncDef configNPY = { "NPYReader", 1, NPYConfigArgs };

static void NPYRegister(void)
{
	iocshRegister(&configNPY, configNPYCallFunc);
}


extern "C"
{
	epicsExportRegistrar(NPYRegister);
}
