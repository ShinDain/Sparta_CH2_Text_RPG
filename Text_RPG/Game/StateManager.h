#pragma once
#include "../CommonInclude.h"
#include "State.h"

class StateManager
{
private:
	StateManager() {};
public:
	virtual ~StateManager();

	static StateManager& GetInstance();

	bool Initialize();
	void Process();

	void ChangeState(StateID nextState);
private:
	bool InitializeStates();
private:
	BaseState* mCurrentState;
	map<StateID, BaseState*> mStates;

public:
	const BaseState* GetCurrnetState() { return mCurrentState; }
};

