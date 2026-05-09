#include "StateManager.h"
#include "../Game/State/State_Initialize.h"
#include "../Game/State/State_SetStat.h"
#include "../Game/State/State_MainMenu.h"
#include "../Game/State/State_Combat.h"
#include "../Game/State/State_CombatEnd.h"
#include "../Game/State/State_Alchemy.h"

StateManager& StateManager::GetInstance()
{
	static StateManager Instance;
	return Instance;
}

StateManager::~StateManager()
{
	for (auto& pair : mStates)
	{
		delete pair.second;
	}

	mStates.clear();
	mCurrentState = nullptr;
}

bool StateManager::Initialize()
{
	if (!InitializeStates())
		return false;

	ChangeState(StateID::Initialize);

	return true;
}

void StateManager::Process()
{
	if (mCurrentState == nullptr)
		return;

	mCurrentState->Process();
	mCurrentState->CheckTransition();
}

bool StateManager::ChangeState(StateID nextState)
{
	if (mStates.find(nextState) != mStates.end())
	{
		if (mCurrentState)
			mCurrentState->Exit();
		mCurrentState = mStates[nextState];
		mCurrentState->Enter();

		return true;
	}

	return false;
}

bool StateManager::InitializeStates()
{
	AddState<State_Initialize>(StateID::Initialize);
	AddState<State_MainMenu>(StateID::MainMenu);
	AddState<State_SetStat>(StateID::SetStat);
	AddState<State_Combat>(StateID::Combat);
	AddState<State_CombatEnd>(StateID::CombatEnd);
	AddState<State_Alchemy>(StateID::Alchemy);

	return true;
}
