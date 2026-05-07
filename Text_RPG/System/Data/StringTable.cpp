#include "StringTable.h"
#include "../FileLoader.h"

StringTable& StringTable::GetInstance()
{
	static StringTable instance;
	return instance;
}

bool StringTable::Load(const string& filePath)
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

void StringTable::ParseString(const string& inString)
{
	if (inString.empty() || inString[0] == '#')
		return;

	size_t pos = inString.find(SPLIT_SYMBOL);
	if (pos != string::npos)
	{
		string key = inString.substr(0, pos);
		string value = inString.substr(pos + 1);

		StringHelper::Trim(key);
		StringHelper::PurifyString(value);
		StringHelper::ReplaceEscapeChar(value);

		mStrings[key] = value;
	}
}

void StringTable::PrintString(const string& key) const
{
	cout << GetString(key);
}

void StringTable::PrintFormatString(const string& key, initializer_list<pair<string, string>> replacements) const
{
	cout << GetFormatString(key, replacements);
}

string StringTable::GetString(const string& key) const
{
	if (mStrings.find(key) != mStrings.end())
	{
		return mStrings.at(key);
	}
		
	return "";
}

string StringTable::GetFormatString(const string& key, initializer_list<pair<string, string>> replacements) const
{
	string formatString = GetString(key);

	for (const auto& item : replacements)
	{
		size_t pos = 0;
		const string& placeholder = item.first;
		const string& value = item.second;
		pos = formatString.find(placeholder, pos);
		formatString.replace(pos, placeholder.length(), value);
	}

	return formatString;
}
