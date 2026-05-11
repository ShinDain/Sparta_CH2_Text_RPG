#pragma once
#include "../State.h"

class Player;
class Monster;

class State_Combat : public BaseState
{
public:
	State_Combat();
protected:
	virtual void Enter() override;
	virtual void Process() override;
private:
	void Action_Attack(Player* player, Monster* target);
	void Action_Item(Player* player);
};
