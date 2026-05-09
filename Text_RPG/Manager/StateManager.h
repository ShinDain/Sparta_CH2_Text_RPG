#pragma once
#include "../CommonInclude.h"
#include "../Game/State.h"

class StateManager
{
private:
	StateManager() {};
public:
	virtual ~StateManager();

	static StateManager& GetInstance();

	bool Initialize();
	void Process();

	bool ChangeState(StateID nextState);
private:
	bool InitializeStates();

	template<typename T>
	void AddState(StateID id);
private:
	BaseState* mCurrentState;
	map<StateID, BaseState*> mStates;

public:
	const BaseState* GetCurrnetState() { return mCurrentState; }
};

template<typename T>
inline void StateManager::AddState(StateID id)
{
	T* menuState = new T();

	if (menuState)
	{
		mStates.emplace(id, menuState);
	}

	return;
}
