#pragma once
#include "../../CommonInclude.h"
#include "../Player.h"

class Thief : public Player
{
public:
	Thief() = delete;
	Thief(string name, int hp, int mp, int Attack, int defence);
	virtual ~Thief();

	virtual bool Initialize() override;

	virtual void Attack(Character* target) override;
};
