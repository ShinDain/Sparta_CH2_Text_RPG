#pragma once
#include "DataTable.h"

struct LevelData
{
	enum class DataOrder
	{
		Level = 0,
		MaxExp,
		IncrementMain,
		IncremantStat,
		End,
	};

	uint32_t Level;
	uint32_t MaxExp;
	uint32_t IncrementMain;
	uint32_t IncrementStat;

	LevelData() = delete;
	LevelData(const vector<string>& dataStrings)
	{
		Level = stoi(dataStrings[(int)LevelData::DataOrder::Level]);
		MaxExp = stoi(dataStrings[(int)LevelData::DataOrder::MaxExp]);
		IncrementMain = stoi(dataStrings[(int)LevelData::DataOrder::IncrementMain]);
		IncrementStat = stoi(dataStrings[(int)LevelData::DataOrder::IncremantStat]);
	}
};

class LevelDataTable : public BaseTable
{
private:
	LevelDataTable() {};
public:
	virtual ~LevelDataTable();

	static LevelDataTable& GetInstance();

	const LevelData* GetLevelData(uint32_t level) const;
protected:
	virtual void ParseString(const string& inString) override;
private:
	vector<LevelData*> mLevelDataList;
};

inline const LevelData* GetLevelData(uint32_t level)
{
	return LevelDataTable::GetInstance().GetLevelData(level);
}