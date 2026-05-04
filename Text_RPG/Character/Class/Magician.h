#pragma once
#include "../../CommonInclude.h"
#include "../Player.h"

class Magician : public Player
{
public:
	Magician() = delete;
	Magician(string name, int hp, int mp, int Attack, int defence);
	virtual ~Magician();

	virtual bool Initialize() override;

	virtual void Attack() override;
};
