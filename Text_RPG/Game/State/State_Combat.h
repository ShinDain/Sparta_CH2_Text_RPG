#pragma once
#include "../State.h"

class State_Combat : public BaseState
{
public:
	State_Combat();
protected:
	virtual void Enter() override;
	virtual void Process() override;
};
