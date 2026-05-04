#pragma once
#include "../CommonInclude.h"
#include "Character.h"
#include "../Component/InventoryComponent.h"

class Player : public Character
{
public:
	enum class Job
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
		Job job;
		string name;

		Class()
			: job(Job::Novice), name("초보자") 
		{}
	};

public:
	Player() = delete;
	Player(string name, int hp, int mp, int Attack, int defence);
	virtual ~Player();

	virtual bool Initialize() override;
	virtual void PrintStats() override;

	void AcquireItem(string itemName, int amount);
	bool UseItem(string itemName);

protected:
	Class mClass;

	InventoryComponent* mInventoryComp;

public:
	virtual string GetClassName() { return mClass.name; }
};

