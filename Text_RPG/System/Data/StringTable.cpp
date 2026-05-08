#include "StringTable.h"
#include "../FileLoader.h"

StringTable& StringTable::GetInstance()
{
	static StringTable instance;
	return instance;
}

void StringTable::ParseString(const string& inString)
{
	if (!IsInvalidString(inString))
		return;

	string key, value;
	SplitString(inString, key, value, DATA_SPLIT_SYMBOL);

	StringHelper::ReplaceEscapeChar(value);

	mStrings[key] = value;
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
		if (pos != string::npos)
		{
			formatString.replace(pos, placeholder.length(), value);
		}
	}

	return formatString;
}
