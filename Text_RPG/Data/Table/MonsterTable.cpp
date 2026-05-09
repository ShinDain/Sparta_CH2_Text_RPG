#include "MonsterTable.h"
#include "../FileLoader.h"

MonsterTable::~MonsterTable()
{
	for (auto& pair : mIndexMap)
	{
		delete pair.second;
	}

	mIndexMap.clear();
	mNameMap.clear();
}

MonsterTable& MonsterTable::GetInstance()
{
	static MonsterTable Instance;
	return Instance;
}

void MonsterTable::ParseString(const string& inString)
{
	if (!IsInvalidString(inString))
		return;

	string key, value;
	SplitString(inString, key, value, DATA_SPLIT_SYMBOL);

	MonsterData* newData = ParseData<MonsterData>(value);
	newData->Index = stoi(key);
	
	mIndexMap[newData->Index] = newData;
	mNameMap[newData->Name] = newData;
}

const MonsterData* MonsterTable::FindMonsterDataByName(const string& name) const
{
	if (mNameMap.find(name) != mNameMap.end())
	{
		return mNameMap.at(name);
	}

	return nullptr;
}

const MonsterData* MonsterTable::FindMonsterDataByIndex(uint32_t index) const
{
	if (mIndexMap.find(index) != mIndexMap.end())
	{
		return mIndexMap.at(index);
	}

	return nullptr;
}
