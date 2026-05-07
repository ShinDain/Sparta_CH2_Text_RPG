#include "StringHelper.h"

void StringHelper::Trim(string& inString)
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

void StringHelper::Unquote(string& inString)
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

void StringHelper::PurifyString(string& inString)
{
	Trim(inString);
	Unquote(inString);
}

void StringHelper::ReplaceEscapeChar(string& string)
{
	size_t pos = 0;
	while ((pos = string.find("\\n", pos)) != string::npos)
	{
		string.replace(pos, 2, "\n");
		++pos;
	}
}
