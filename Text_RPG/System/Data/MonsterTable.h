#pragma once
#include "DataTable.h"

struct MonsterData
{
	enum class DataOrder
	{
		Name = 0,
		Level,
		HP,
		MP,
		Attack,
		Defence,
		DropItemname,
		End,
	};

	int Index;
	string Name;
	uint32_t Level;
	uint32_t HP;
	uint32_t MP;
	uint32_t Attack;
	uint32_t Defence;
	string DropItemName;

	MonsterData() = delete;
	MonsterData(const vector<string>& dataStrings)
		: Index(-1)
	{
		Name = dataStrings[(int)MonsterData::DataOrder::Name];
		Level = stoi(dataStrings[(int)MonsterData::DataOrder::Level]);
		HP = stoi(dataStrings[(int)MonsterData::DataOrder::HP]);
		MP = stoi(dataStrings[(int)MonsterData::DataOrder::MP]);
		Attack = stoi(dataStrings[(int)MonsterData::DataOrder::Attack]);
		Defence = stoi(dataStrings[(int)MonsterData::DataOrder::Defence]);
		DropItemName = dataStrings[(int)MonsterData::DataOrder::DropItemname];
	}
};

class MonsterTable : public BaseTable
{
private:
	MonsterTable() {};
public:
	virtual ~MonsterTable();

	static MonsterTable& GetInstance();

	const MonsterData* FindMonsterDataByName(const string& name) const;
	const MonsterData* FindMonsterDataByIndex(uint32_t index) const;

protected:
	virtual void ParseString(const string& inString) override;
private:
	map<string, const MonsterData*> mNameMap;
	map<int, const MonsterData*> mIndexMap;
};

inline const MonsterData* FindMonsterDataByName(const string& name)
{
	return MonsterTable::GetInstance().FindMonsterDataByName(name);
}
inline const MonsterData* FindMonsterDataByIndex(uint32_t index)
{
	return MonsterTable::GetInstance().FindMonsterDataByIndex(index);
}
