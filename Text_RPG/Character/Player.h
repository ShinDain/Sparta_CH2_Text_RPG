#pragma once
#include "../CommonInclude.h"
#include "Character.h"
#include "../Component/InventoryComponent.h"

class Player : public Character
{
public:
	enum class PlayerJob
	{
		Novice,
		Warrior,
		Magician,
		Thief,
		Archer,
		End,
	};

	struct Class
	{
		PlayerJob Job;
		string Name;

		Class()
			: Job(PlayerJob::Novice), Name("초보자")
		{}
	};

public:
	Player() = delete;
	Player(string name, int hp, int mp, int Attack, int defence);
	virtual ~Player();

	virtual bool Initialize() override;
	virtual void PrintStats() override;

	void AcquireItem(ItemData data, int amount);
	bool UseItem(string itemName);

	void PrintInventory();
protected:
	Class mClass;

	InventoryComponent* mInventoryComp;

public:
	virtual string GetClassName() { return mClass.Name; }
};

