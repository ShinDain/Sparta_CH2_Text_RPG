#include "State.h"
#include "../Manager/StateManager.h"

Transition::Transition(Condition* condition, StateID nextState)
	: mCondition(condition), mNextStateID(nextState)
{
}

Transition::~Transition()
{
	delete mCondition;
}

void Transition::InitTransition()
{
	mCondition->Init();
}

bool Transition::CanTransition() const
{
	if (!mCondition)
		return false;

	return mCondition->Check(); 
}

BaseState::BaseState()
{
	mTransitions = {};
}

BaseState::~BaseState()
{
	for (const auto& pair : mTransitions)
	{
		delete pair.second;
	}
}

StateID BaseState::CanTransition() const
{
	for (const auto& pair : mTransitions)
	{
		Transition* transition = pair.second;

		if (!transition)
			continue;

		if (transition->CanTransition())
		{
			return pair.first;
		}
	}

	return StateID::End;
}

bool BaseState::CheckTransition()
{
	StateID nextState = StateID::End;
	if ((nextState = CanTransition()) != StateID::End)
	{
		return StateManager::GetInstance().ChangeState(nextState);
	}
	return false;
}

void BaseState::Exit()
{
	InitTransition();
}

void BaseState::InitTransition()
{
	for (auto& pair : mTransitions)
	{
		Transition* transition = pair.second;
		if (transition)
		{
			transition->InitTransition();
		}
	}
}
