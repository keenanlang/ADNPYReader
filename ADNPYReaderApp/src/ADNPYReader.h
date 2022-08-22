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
	
	protected:
		void addParam(const char* name, asynParamType type);
	
		std::map<std::string, int> params;
};

#define ADNPY_FilePath      "ADNPY_FILE_PATH"


#endif
