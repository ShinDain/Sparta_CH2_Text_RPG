#include "State_Initialize.h"
#include "../StateManager.h"
#include "../Conditions/AlwaysTrueCondition.h"

State_Initialize::State_Initialize()
{
	mName = "Initialize";
	AlwaysTrueCondition* condition = new AlwaysTrueCondition();
	Transition* transition = new Transition(condition, StateID::MainMenu);
	mTransition = transition;
}

void State_Initialize::Enter()
{
	cout << "초기화 state 진입 \n" << endl;
}

void State_Initialize::Process()
{
	cout << "초기화 state 진행 \n" << endl;
}

void State_Initialize::Exit()
{
	cout << "초기화 state 퇴장 \n" << endl;
}
