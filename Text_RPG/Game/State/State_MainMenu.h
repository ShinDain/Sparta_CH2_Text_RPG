#pragma once
#include "../State.h"

class State_MainMenu : public BaseState
{
public:
	State_MainMenu();
protected:
	virtual void Enter() override;
	virtual void Process() override;
	virtual void Exit() override;
};

