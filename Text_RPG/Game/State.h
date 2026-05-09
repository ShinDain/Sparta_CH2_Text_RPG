#pragma once
#include "../CommonInclude.h"

class StateManager;

enum class StateID
{
	Initialize = 0,
	SetStat,
	MainMenu,
	Combat,
	CombatEnd,
	Alchemy,
	End,
};

class Condition
{
public:
	virtual bool Check() = 0;
};

class Transition
{
public:
	Transition() = delete;
	Transition(Condition* condition, StateID nextState);
	virtual ~Transition();

	StateID GetNextStateID() { return mNextStateID; }
	bool CanTransition();
protected:
	Condition* mCondition;
	StateID mNextStateID;
};

class IState
{
	friend StateManager;

protected:
	virtual void Enter() = 0;
	virtual void Process() = 0;
	virtual void Exit() = 0;
};

class BaseState : public IState
{
protected:
	BaseState();
public:
	virtual ~BaseState();

	bool CanTransition();
	bool CheckTransition();
protected:
	string mName;
	Transition* mTransition;
};
