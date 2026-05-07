#include "StringTable.h"
#include "../FileLoader.h"

map<string, string> StringTable::mStrings = {};
string StringTable::mPath = "";

StringTable::StringTable()
{
}

StringTable::~StringTable()
{
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

	mPath = filePath;

	return true;
}

void StringTable::Trim(string& inString)
{
	inString.erase(find_if(inString.rbegin(), inString.rend(), [](unsigned char ch)
		{
			return !std::isspace(ch);
		}).base(), inString.end());

	inString.erase(inString.begin(), find_if(inString.begin(), inString.end(), [](unsigned char ch)
		{
			return !std::isspace(ch);
		}));
}

void StringTable::Unquote(string& inString)
{
	inString.erase(find_if(inString.rbegin(), inString.rend(), [](char ch)
		{
			return ch == '\"' ? false : true;
		}).base(), inString.end());

	inString.erase(inString.begin(), find_if(inString.begin(), inString.end(), [](char ch)
		{
			return ch == '\"' ? false : true;
		}));
}

void StringTable::ParseString(const string& inString)
{
	if (inString.empty() || inString[0] == '#')
		return;

	char symbol = ':';
	
	size_t pos = inString.find(symbol);
	if (pos != string::npos)
	{
		string key = inString.substr(0, pos);
		string value = inString.substr(pos + 1);

		Trim(key);
		Trim(value);
		Unquote(value);
		ReplaceEscapeChar(value);

		mStrings[key] = value;
	}
}

void StringTable::ReplaceEscapeChar(string& string)
{
	size_t pos = 0;
	while ((pos = string.find("\\n", pos)) != string::npos)
	{
		string.replace(pos, 2, "\n");
		++pos;
	}
}

StringTable StringTable::Get()
{
	static StringTable instance;
	return instance;
}

void StringTable::PrintString(const string& key)
{
	cout << GetString(key);
}

void StringTable::PrintFormatString(const string& key, initializer_list<pair<string, string>> replacements)
{
	cout << GetFormatString(key, replacements);
}

string StringTable::GetString(const string& key)
{
	if (mStrings.find(key) != mStrings.end())
	{
		return mStrings[key];
	}
		
	return "";
}

string StringTable::GetFormatString(const string& key, initializer_list<pair<string, string>> replacements)
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
