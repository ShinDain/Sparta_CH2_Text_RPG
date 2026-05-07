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

	ItemData()
		:Index(-1), Name("None"), Price(0) {
	}
	ItemData(string name, int price)
		:Index(-1), Name(name), Price(price) {
	}
};

class ItemTable : public IDataTable
{
private:
	ItemTable() {};
	ItemTable(const ItemTable& rhs) = delete;
	ItemTable operator=(const ItemTable& rhs) = delete;
public:
	virtual ~ItemTable();

	static ItemTable& GetInstance();
	virtual bool Load(const string& filePath) override;

	const ItemData* FindItemDataByName(const string& name) const;
	const ItemData* FindItemDataByIndex(uint32_t idx) const;

protected:
	virtual void ParseString(const string& inString) override;

	ItemData* ParseItemData(const string& inString);
private:
	map<string, uint32_t> mItemDataIndexMap;
	vector<ItemData*> mItemDataList;
};

inline const ItemData* FindItemDataByName(const string& name)
{
	return ItemTable::GetInstance().FindItemDataByName(name);
}

inline const ItemData* FindItemDataByIndex(uint32_t idx)
{
	return ItemTable::GetInstance().FindItemDataByIndex(idx);
}
