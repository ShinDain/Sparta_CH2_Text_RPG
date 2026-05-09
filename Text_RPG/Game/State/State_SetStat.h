#pragma once
#include "../State.h"

class State_SetStat : public BaseState
{
public:
	State_SetStat();
protected:
	virtual void Enter() override;
	virtual void Process() override;
};
