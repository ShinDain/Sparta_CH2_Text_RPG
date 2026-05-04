#pragma once
#include "../CommonInclude.h"
#include "Character.h"
#include "../Item/Item.h"

class Monster : public Character
{
public:
	Monster() = delete;
	Monster(string name, int hp, int mp, int Attack, int defence);
	virtual ~Monster();

	virtual bool Initialize() override;
	virtual void PrintStats() override;

	virtual void Attack(class Character* target) override;
protected:
	ItemData mDropItemData;
public:
	string GetDropItemName() { return mDropItemData.Name; }
	int GetDropItemPrice() { return mDropItemData.Price; }
	ItemData GetDropItemData() { return mDropItemData; }

	void SetDropItemData(ItemData dropItemData) { mDropItemData = dropItemData; }
};

