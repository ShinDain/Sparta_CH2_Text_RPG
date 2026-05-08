#include "ItemTable.h"
#include "../FileLoader.h"

ItemTable::~ItemTable()
{
	for (auto& pair : mIndexMap)
	{
		delete pair.second;
	}

	mIndexMap.clear();
	mNameMap.clear();
}

ItemTable& ItemTable::GetInstance()
{
	static ItemTable instance;
	return instance;
}

void ItemTable::ParseString(const string& inString)
{
	if (!IsInvalidString(inString))
		return;

	string key, value;
	SplitString(inString, key, value, DATA_SPLIT_SYMBOL);

	ItemData* newData = ParseData<ItemData>(value);
	newData->Index = stoi(key);

	mIndexMap[newData->Index] = newData;
	mNameMap[newData->Name] = newData;
}

const ItemData* ItemTable::FindItemDataByName(const string& name) const
{
	if (mNameMap.find(name) != mNameMap.end())
	{
		return mNameMap.at(name);
	}

	return nullptr;
}

const ItemData* ItemTable::FindItemDataByIndex(uint32_t index) const
{
	if (mIndexMap.find(index) != mIndexMap.end())
	{
		return mIndexMap.at(index);
	}

	return nullptr;
}
