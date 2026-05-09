#pragma once
#include "../State.h"

class State_Initialize : public BaseState
{
public:
	State_Initialize();
protected:
	virtual void Enter() override;
	virtual void Process() override;
	virtual void Exit() override;
};
