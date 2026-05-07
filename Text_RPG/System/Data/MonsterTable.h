#pragma once
#include "DataTable.h"

struct MonsterData
{
	enum class DataOrder
	{
		Name = 0,
		HP = 1,
		MP = 2,
		Attack = 3,
		Defence = 4,
		DropItemname = 5,
		End,
	};

	int Index;
	string Name;
	uint32_t HP;
	uint32_t MP;
	uint32_t Attack;
	uint32_t Defence;
	string DropItemName;
};

class MonsterTable : public IDataTable
{
private:
	MonsterTable() {};
public:
	virtual ~MonsterTable();

	static MonsterTable& GetInstance();
	virtual bool Load(const string& filePath) override;

	const MonsterData* FindMonsterDataByName(const string& name) const;
	const MonsterData* FindMonsterDataByIndex(uint32_t index) const;

protected:
	virtual void ParseString(const string& inString) override;

	MonsterData* ParseMonsterData(const string& inString);
private:
	map<string, uint32_t> mMonsterDataIndexMap;
	vector<MonsterData*> mMonsterDataList;
};

inline const MonsterData* FindMonsterDataByName(const string& name)
{
	return MonsterTable::GetInstance().FindMonsterDataByName(name);
}
inline const MonsterData* FindMonsterDataByIndex(uint32_t index)
{
	return MonsterTable::GetInstance().FindMonsterDataByIndex(index);
}
