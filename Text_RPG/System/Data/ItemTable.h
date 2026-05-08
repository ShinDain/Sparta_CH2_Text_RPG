#pragma once
#include "DataTable.h"

struct ItemData
{
	enum class DataOrder
	{
		Name = 0,
		Price = 1,
		End,
	};

	int Index;
	string Name;
	int Price;

	ItemData() = delete;
	ItemData(const vector<string>& dataStrings)
		: Index(-1)
	{
		Name = dataStrings[(int)ItemData::DataOrder::Name];
		Price = stoi(dataStrings[(int)ItemData::DataOrder::Price]);
	}
};

class ItemTable : public BaseTable
{
private:
	ItemTable() {};
	ItemTable(const ItemTable& rhs) = delete;
	ItemTable operator=(const ItemTable& rhs) = delete;
public:
	virtual ~ItemTable();

	static ItemTable& GetInstance();

	const ItemData* FindItemDataByName(const string& name) const;
	const ItemData* FindItemDataByIndex(uint32_t index) const;

protected:
	virtual void ParseString(const string& inString) override;
private:
	map<int, const ItemData*> mIndexMap;
	map<string, const ItemData*> mNameMap;
};

inline const ItemData* FindItemDataByName(const string& name)
{
	return ItemTable::GetInstance().FindItemDataByName(name);
}

inline const ItemData* FindItemDataByIndex(uint32_t index)
{
	return ItemTable::GetInstance().FindItemDataByIndex(index);
}
