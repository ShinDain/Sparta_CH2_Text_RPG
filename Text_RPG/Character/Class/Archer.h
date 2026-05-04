#pragma once
#include "../../CommonInclude.h"
#include "../Player.h"

class Archer : public Player
{
public:
	Archer() = delete;
	Archer(string name, int hp, int mp, int Attack, int defence);
	virtual ~Archer();

	virtual bool Initialize() override;

	virtual void Attack() override;
};
