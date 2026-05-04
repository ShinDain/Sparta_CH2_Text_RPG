#pragma once
#include "../../CommonInclude.h"
#include "../Player.h"

class Warrior : public Player
{
public:
	Warrior() = delete;
	Warrior(string name, int hp, int mp, int Attack, int defence);
	virtual ~Warrior();

	virtual bool Initialize() override;

	virtual void Attack(Character* target) override;

};
