#ifndef INC_ADNPYREADER_H
#define INC_ADNPYREADER_H

#include <map>
#include <string>

#include <shareLib.h>

#include "ADDriver.h"


class epicsShareClass ADNPYReader: public ADDriver
{
	public:
		ADNPYReader(const char* portname);
		
		virtual asynStatus writeInt32(asynUser *pasynUser, epicsInt32 value);
	
	protected:
		void addParam(const char* name, asynParamType type);
	
		std::map<std::string, int> params;
};

#define ADNPY_FilePath      "ADNPY_FILE_PATH"


#endif
