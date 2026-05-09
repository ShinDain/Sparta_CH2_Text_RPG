#include "FileLoader.h"
#include <fstream>
#include <iostream>

bool FileLoader::Load(const std::string& filePath, vector<string>& outStrings)
{
	ifstream readFile(filePath);

	if (readFile.is_open())
	{
		readFile.seekg(0, ios::end);
		streamsize size = readFile.tellg();
		readFile.seekg(0, ios::beg);

		// 한줄에 50자 미만이라 가정하고 먼저 할당
		outStrings.reserve(static_cast<size_t>(size / 50));

		string cacheStr = "";
		while (getline(readFile, cacheStr))
		{
			if (cacheStr[0] == '#')
			{
				continue;	
			}
			outStrings.push_back(cacheStr);
		}
	}
	else
	{
		cout << "올바르지 않은 파일 경로 입니다.\n FilePath : " << filePath << endl;
		return false;
	}

	readFile.close();

	return true;
}
