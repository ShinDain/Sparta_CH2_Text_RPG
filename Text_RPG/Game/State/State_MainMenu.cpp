#include "State_MainMenu.h"
#include "../Conditions/AlwaysTrueCondition.h"

State_MainMenu::State_MainMenu()
{
	mName = "MainMenu";
	AlwaysTrueCondition* condition = new AlwaysTrueCondition();
	Transition* transition = new Transition(condition, StateID::MainMenu);
	mTransition = transition;
}

void State_MainMenu::Enter()
{
	cout << "메뉴 state 진입 \n" << endl;
}

void State_MainMenu::Process()
{
	cout << "메뉴 state 진행 \n" << endl;
}

void State_MainMenu::Exit()
{
	cout << "메뉴 state 퇴장 \n" << endl;
}
