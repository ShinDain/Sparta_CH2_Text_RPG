#pragma once
#include "../CommonInclude.h"
#include "Character.h"
//#include "../System/Data/ItemTable.h"
#include "../System/Data/MonsterTable.h"

class Monster : public Character
{
public:
	Monster() = delete;
	Monster(const MonsterData* data);
	virtual ~Monster();

	virtual bool Initialize() override;
	virtual void PrintStats() override;

	virtual void Attack(class Character* target) override;
protected:
	const MonsterData* mData;
	string mDropItemName;
public:
	string GetDropItemName() { return mDropItemName; }
};

