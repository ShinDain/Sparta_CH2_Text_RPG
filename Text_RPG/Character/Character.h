#pragma once
#include <string>;

using namespace std;

const int SIZE = 4;

class Character
{
public:
	enum class STAT_INDEX
	{
		HP = 0,
		MP = 1,
		ATTACK = 2,
		DEFENCE = 3,
		END,
	};

public:
	Character();
	Character(const string& InName);
	virtual ~Character();

	bool Initialize();

	void PrintStats();
protected:
	bool InitializeName();
	bool InitializeTwoStats(STAT_INDEX StatIndex1, STAT_INDEX StatIndex2);

	bool IsValidStatValue(STAT_INDEX StatIndex, int InValue);
protected:
	string mName;

	int mStats[SIZE];

public:
	string GetName() const { return mName; }
	int GetHP() const { return mStats[(int)STAT_INDEX::HP]; }
	int GetMP() const { return mStats[(int)STAT_INDEX::MP]; }
	int GetAttack() const { return mStats[(int)STAT_INDEX::ATTACK]; }
	int GetDefence() const { return mStats[(int)STAT_INDEX::DEFENCE]; }

	//void SetMP(int InValue) { mStats[(int)STAT_INDEX::MP] = InValue; }
	//void SetName(const string& InName) { mName = InName; }
	//void SetHP(int InValue) { mStats[(int)STAT_INDEX::HP] = InValue; }
	//void SetAttack(int InValue) { mStats[(int)STAT_INDEX::ATTACK] = InValue; }
	//void SetDefence(int InValue) { mStats[(int)STAT_INDEX::DEFENCE] = InValue; }
};

