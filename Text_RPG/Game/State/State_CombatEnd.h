#pragma once
#include "../State.h"

class State_CombatEnd : public BaseState
{
public:
	State_CombatEnd();
protected:
	virtual void Enter() override;
	virtual void Process() override;
};
