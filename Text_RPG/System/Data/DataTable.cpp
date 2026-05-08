#include "DataTable.h"
#include "../FileLoader.h"

bool BaseTable::Load(const string& filePath)
{
	vector<string> rawStrings;
	if (!FileLoader::Load(filePath, rawStrings))
		return false;

	for (string str : rawStrings)
	{
		ParseString(str);
	}

	return true;
}

bool BaseTable::IsInvalidString(const string& inString)
{
	if (inString.empty() || inString[0] == '#')
		return false;

	return true;
}

void BaseTable::SplitString(const string& inString, string& outkey, string& outValue, const char splitSymbol)
{
	vector<string> splitedStrings;
	SplitString(inString, splitedStrings, splitSymbol);

	if (splitedStrings.size() >= 2)
	{
		outkey = splitedStrings[0];
		outValue = splitedStrings[1];
	}
}

void BaseTable::SplitString(const string& inString, vector<string>& outStrings, const char splitSymbol)
{
	size_t pos = 0;
	size_t lastPos = 0;
	vector<string> rawDatas = {};
	while ((pos = inString.find(splitSymbol, pos)) != string::npos)
	{
		string value = inString.substr(lastPos, pos);

		StringHelper::PurifyString(value);
		rawDatas.emplace_back(value);

		++pos;
		lastPos = pos;
	}

	string lastValue = inString.substr(lastPos);
	StringHelper::PurifyString(lastValue);
	rawDatas.emplace_back(lastValue);

	outStrings = move(rawDatas);
	return;
}
