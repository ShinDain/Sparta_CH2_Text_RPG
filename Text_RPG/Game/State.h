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
	virtual void Init() {};
	virtual void OnNotify() {};
	virtual bool Check() = 0;
};

class Transition
{
public:
	Transition() = delete;
	Transition(Condition* condition, StateID nextState);
	virtual ~Transition();

	void InitTransition();

	StateID GetNextStateID() { return mNextStateID; }
	bool CanTransition() const;

	void Notify() { mCondition->OnNotify(); }
	Condition* GetCondition() { return mCondition; }
protected:
	Condition* mCondition;
	StateID mNextStateID;
};

class IState
{
protected:
	virtual void Enter() = 0;
	virtual void Process() = 0;
	virtual void Exit() = 0;
};

class BaseState : public IState
{
	friend StateManager;

protected:
	BaseState();
public:
	virtual ~BaseState();

	StateID CanTransition() const;
	bool CheckTransition();
protected:
	virtual void Exit() override;
	void InitTransition();

	template<typename T>
	void AddTransition(StateID state);
protected:
	string mName;
	map<StateID, Transition*> mTransitions;
public:
	string GetName() { return mName; }
};

template<typename T>
inline void BaseState::AddTransition(StateID state)
{
	StateID destState = state;
	T* condition = new T();
	Transition* transition = new Transition(condition, destState);
	mTransitions.emplace(destState, transition);
}
