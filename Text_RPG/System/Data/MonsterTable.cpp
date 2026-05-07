#include "MonsterTable.h"
#include "../FileLoader.h"

MonsterTable::~MonsterTable()
{
	for (auto& data : mMonsterDataList)
	{
		delete data;
		data = nullptr;
	}
}

MonsterTable& MonsterTable::GetInstance()
{
	static MonsterTable Instance;
	return Instance;
}

bool MonsterTable::Load(const string& filePath)
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

void MonsterTable::ParseString(const string& inString)
{
	if (inString.empty() || inString[0] == '#')
		return;

	size_t pos = inString.find(SPLIT_SYMBOL);
	if (pos != string::npos)
	{
		string key = inString.substr(0, pos);
		string value = inString.substr(pos + 1);

		StringHelper::Trim(key);
		StringHelper::Trim(value);

		MonsterData* newData = ParseMonsterData(value);
		newData->Index = stoi(key);

		mMonsterDataIndexMap[newData->Name] = newData->Index;
		mMonsterDataList.emplace_back(newData);
	}
}

MonsterData* MonsterTable::ParseMonsterData(const string& inString)
{
	MonsterData* newData = new MonsterData();

	size_t pos = 0;
	size_t lastPos = 0;
	vector<string> rawDatas = {};
	while ((pos = inString.find(',', pos)) != string::npos)
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

	newData->Name = rawDatas[(int)MonsterData::DataOrder::Name];
	newData->HP = stoi(rawDatas[(int)MonsterData::DataOrder::HP]);
	newData->MP = stoi(rawDatas[(int)MonsterData::DataOrder::MP]);
	newData->Attack = stoi(rawDatas[(int)MonsterData::DataOrder::Attack]);
	newData->Defence = stoi(rawDatas[(int)MonsterData::DataOrder::Defence]);
	newData->DropItemName = rawDatas[(int)MonsterData::DataOrder::DropItemname];

	return newData;
}

const MonsterData* MonsterTable::FindMonsterDataByName(const string& name) const
{
	if (mMonsterDataIndexMap.find(name) != mMonsterDataIndexMap.end())
	{
		return mMonsterDataList[mMonsterDataIndexMap.at(name)];
	}

	return nullptr;
}

const MonsterData* MonsterTable::FindMonsterDataByIndex(uint32_t index) const
{
	if (index < mMonsterDataList.size())
	{
		return mMonsterDataList[index];
	}

	return nullptr;
}
