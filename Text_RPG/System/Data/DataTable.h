#pragma once
#include "../../CommonInclude.h"
#include "../StringHelper.h"

const char SPLIT_SYMBOL = ':';

class IDataTable
{
public:
	virtual bool Load(const string& filePath) = 0;

protected:
	virtual void ParseString(const string& inString) = 0;
};
