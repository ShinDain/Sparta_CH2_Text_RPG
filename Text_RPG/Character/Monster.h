#pragma once
#include "../CommonInclude.h"
#include "Character.h"

class Monster : public Character
{
public:
	Monster() = delete;
	Monster(string name, int hp, int mp, int Attack, int defence);
	virtual ~Monster();

	virtual void PrintStats() override;

	virtual void Attack(class Character* target) override;
protected:
	string mDropItemName;
	int mDropItemPrice;

public:
	string GetDropItemName() { return mDropItemName; }
};

