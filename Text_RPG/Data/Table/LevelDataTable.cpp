#include "LevelDataTable.h"

LevelDataTable::~LevelDataTable()
{
	for (auto& data : mLevelDataList)
	{
		delete data;
	}

	mLevelDataList.clear();
}

LevelDataTable& LevelDataTable::GetInstance()
{
	static LevelDataTable Instance;
	return Instance;
}

void LevelDataTable::ParseString(const string& inString)
{
	if (!IsInvalidString(inString))
		return;

	string key, value;
	SplitString(inString, key, value, DATA_SPLIT_SYMBOL);

	LevelData* newData = ParseData<LevelData>(value);
	mLevelDataList.emplace_back(newData);
}

const LevelData* LevelDataTable::GetLevelData(uint32_t level) const
{
	if (level >= mLevelDataList.size()
		|| level < 1)
		return nullptr;

	return mLevelDataList[level - 1];
}