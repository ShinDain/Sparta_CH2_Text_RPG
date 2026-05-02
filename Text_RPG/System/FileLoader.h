#pragma once
#include <string>
#include <vector>

using namespace std;

class FileLoader
{
public:
	static bool Load(const string& filePath, vector<string>& outStrings);
};

