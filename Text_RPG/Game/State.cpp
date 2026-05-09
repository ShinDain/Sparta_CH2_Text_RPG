#include "State.h"
#include "StateManager.h"

Transition::Transition(Condition* condition, StateID nextState)
	: mCondition(condition), mNextStateID(nextState)
{
}

Transition::~Transition()
{
	delete mCondition;
}

bool Transition::CanTransition()
{
	if (!mCondition)
		return false;

	return mCondition->Check(); 
}

BaseState::BaseState()
{
	mTransition = nullptr;
}

BaseState::~BaseState()
{
	delete mTransition;
}

bool BaseState::CanTransition()
{
	if (!mTransition)
		return false;
	
	return mTransition->CanTransition();
}

bool BaseState::CheckTransition()
{
	if (CanTransition())
	{
		StateManager::GetInstance().ChangeState(StateID::MainMenu);

		return true;
	}
	return false;
}
