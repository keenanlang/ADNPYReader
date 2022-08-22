#include "ADNPYReader.h"

ADNPYReader::ADNPYReader(const char* portname) :
	ADDriver(portName,
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
	setStringParam(params[ADNPY_FilePath], "");
}

ADNPYReader::addParam(const char* paramname, asynParamType type)
{
	int tempval;
	std::string key(paramname);
	
	createParam( paramname, type, &tempval);
	
	this->params[key] = tempval;
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
