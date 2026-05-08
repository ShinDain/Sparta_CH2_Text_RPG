#pragma once
#include "../../CommonInclude.h"
#include "../StringHelper.h"

const char DATA_SPLIT_SYMBOL = ';';
const char VALUE_SPLIT_SYMBOL = ',';

class IDataTable
{
public:
	virtual bool Load(const string& filePath) = 0;

protected:
	virtual void ParseString(const string& inString) = 0;
};

class BaseTable : public IDataTable
{
public:
	virtual bool Load(const string& filePath) override;
protected:
	bool IsInvalidString(const string& inString);
	void SplitString(const string& inString, string& outkey, string& outValue, const char splitSymbol);
	void SplitString(const string& inString, vector<string>& outStrings, const char splitSymbol);

	template<typename T>
	T* ParseData(const string& inString);
};

template<typename T>
inline T* BaseTable::ParseData(const string& inString)
{
	vector<string> rawDatas = {};
	SplitString(inString, rawDatas, VALUE_SPLIT_SYMBOL);

	T* newData = new T(rawDatas);

	return newData;
}
