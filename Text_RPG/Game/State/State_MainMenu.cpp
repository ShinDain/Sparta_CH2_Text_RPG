#include "State_MainMenu.h"
#include "../Conditions/TriggerCondition.h"

#include "../Game.h"
#include "../../Manager/ObjectManager.h"
#include "../../Data/Table/StringTable.h"
#include "../../Character/Player.h"

State_MainMenu::State_MainMenu()
{
	mName = "MainMenu";
	AddTransition<TriggerCondition>(StateID::Alchemy);
	AddTransition<TriggerCondition>(StateID::Combat);
	AddTransition<TriggerCondition>(StateID::SetStat);
}

void State_MainMenu::Enter()
{
	PrintString("alchemy_move_menu");
}

void State_MainMenu::Process()
{
	PrintString("menu_select_1");
	PrintString("menu_select_2");
	PrintString("menu_select_3");
	PrintString("menu_select_4");
	PrintString("menu_select_5");
	PrintString("menu_select_6");
	PrintString("menu_select_7");
	PrintString("double_line");
	PrintString("input_number");

	int input = 0;
	cin >> input;

	Player* player = dynamic_cast<Player*>(ObjectManager::GetInstance().mPlayer);
	switch (input)
	{
	case 0:
		PrintString("game_exit");
		Game::GetInstance().ShutDown();
		break;
	case 1:
		mTransitions[StateID::Combat]->Notify();
		break;
	case 2:
		player->PrintInventory();
		break;
	case 3:
		mTransitions[StateID::Alchemy]->Notify();
		break;
	case 4:
		player->PrintStats();
		break;
	case 5:
		mTransitions[StateID::SetStat]->Notify();
		break;
	default:
		PrintString("invalid_input");
		break;
	}
}
