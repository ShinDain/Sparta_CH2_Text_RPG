#pragma once
#include "../CommonInclude.h"

class StringHelper
{
public:
	StringHelper() = delete;

	static void Trim(string& inString);
	static void Unquote(string& inString);
	static void PurifyString(string& inString);

	static void ReplaceEscapeChar(string& inString);
};

