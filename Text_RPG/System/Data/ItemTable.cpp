#include "ItemTable.h"
#include "../FileLoader.h"

ItemTable::~ItemTable()
{
	for (auto& data : mItemDataList)
	{
		delete data;
		data = nullptr;
	}
}

ItemTable& ItemTable::GetInstance()
{
	static ItemTable instance;
	return instance;
}

bool ItemTable::Load(const string& filePath)
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

void ItemTable::ParseString(const string& inString)
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

		ItemData* newData = ParseItemData(value);
		newData->Index = stoi(key);

		mItemDataIndexMap[newData->Name] = newData->Index;
		mItemDataList.emplace_back(newData);
	}

}

ItemData* ItemTable::ParseItemData(const string& inString)
{
	ItemData* newData = new ItemData();

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

	newData->Name = rawDatas[(int)ItemData::DataOrder::Name];
	int price = stoi(rawDatas[(int)ItemData::DataOrder::Price]);
	newData->Price = price;

	return newData;
}

const ItemData* ItemTable::FindItemDataByName(const string& name) const
{
	if (mItemDataIndexMap.find(name) != mItemDataIndexMap.end())
	{
		return mItemDataList[mItemDataIndexMap.at(name)];
	}

	return nullptr;
}

const ItemData* ItemTable::FindItemDataByIndex(uint32_t idx) const
{
	if (idx < mItemDataList.size())
	{
		return mItemDataList[idx];
	}

	return nullptr;
}
