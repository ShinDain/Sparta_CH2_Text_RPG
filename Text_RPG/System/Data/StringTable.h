#pragma once
#include "../../CommonInclude.h"

class StringTable
{
private:
	StringTable();
public:
	virtual ~StringTable();

    bool Load(const string& filePath);
	static void Trim(string& inString);
	static void Unquote(string& inString);

	static StringTable Get();
	static void PrintString(const string& key);
	static void PrintFormatString(const string& key, initializer_list<pair<string, string>> replacements);
	static string GetString(const string& key);
	static string GetFormatString(const string& key, initializer_list<pair<string, string>> replacements);

	static string GetPath()
	{
		return mPath;
	}
private:
	void ParseString(const string& inString);
	void ReplaceEscapeChar(string& string);

private:
	static string mPath;
	static map<string, string> mStrings;
};

