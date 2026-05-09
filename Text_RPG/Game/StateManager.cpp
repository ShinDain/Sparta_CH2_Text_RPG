#include "StateManager.h"
#include "State/State_Initialize.h"
#include "State/State_MainMenu.h"

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

void StateManager::ChangeState(StateID nextState)
{
	if (mStates.find(nextState) != mStates.end())
	{
		if (mCurrentState)
			mCurrentState->Exit();
		mCurrentState = mStates[nextState];
		mCurrentState->Enter();
	}
}

bool StateManager::InitializeStates()
{
	BaseState* initState = new State_Initialize();
	if (initState)
	{
		mStates.emplace(StateID::Initialize, initState);
	}
	else
		return false;

	BaseState* menuState = new State_MainMenu();
	if (menuState)
	{
		mStates.emplace(StateID::MainMenu, menuState);
	}
	else
		return false;

	return true;
}
