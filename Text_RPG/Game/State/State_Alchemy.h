#pragma once
#include "../State.h"

class State_Alchemy : public BaseState
{
public:
	State_Alchemy();
protected:
	virtual void Enter() override;
	virtual void Process() override;
};
