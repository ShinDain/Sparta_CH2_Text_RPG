#pragma once
#include "../Character.h"
#include "../../System/Data/MonsterTable.h"

const int DEFAULT_REWARD_EXP = 30;

class Monster : public Character
{
public:
	Monster() = delete;
	Monster(const MonsterData* data);
	virtual ~Monster();

	virtual bool Initialize() override;
	virtual void PrintStats() override;

	virtual void Attack(class Character* target) override;

	int GetRewardExp(int opponentLevel);

protected:
	const MonsterData* mData;
	string mDropItemName;
public:
	string GetDropItemName() { return mDropItemName; }
};

