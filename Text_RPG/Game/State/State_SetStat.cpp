#include "State_SetStat.h"
#include "../Conditions/TriggerCondition.h"

#include "../../Data/Table/StringTable.h"
#include "../../Character/Player.h"
#include "../../Manager/ObjectManager.h"

State_SetStat::State_SetStat()
{
	mName = "SetStat";
	AddTransition<TriggerCondition>(StateID::MainMenu);
}

void State_SetStat::Enter()
{
	PrintString("menu_move_stat");
}

void State_SetStat::Process()
{
	PrintString("stat_setting_1");
	PrintString("stat_setting_2");
	PrintString("stat_setting_3");
	PrintString("stat_setting_4");
	PrintString("double_line");
	PrintString("input_number");

	string input = {};
	cin >> input;

	int select = stoi(input);

	Player* player = ObjectManager::GetInstance().mPlayer;

	switch (select)
	{
	case 0:
	{
		PrintString("game_start");
		mTransitions[StateID::MainMenu]->Notify();
	}
		break;
	case 1:
	{
		string itemName = "HP포션";
		bool result = player->UseItem(itemName);
		if (!result)
		{
			PrintFormatString("item_use_not_enough", { {"{ItemName}", itemName} });
		}
		else
		{
			player->RecoveryHP(20, itemName);
		}
	}
	break;
	case 2:
	{
		string itemName = "MP포션";
		bool result = player->UseItem(itemName);
		if (!result)
		{
			PrintFormatString("item_use_not_enough", { {"{ItemName}", itemName} });
		}
		else
		{
			player->RecoveryMP(20, itemName);
		}
	}
	break;
	case 3:
	{
		int resultAttack = player->GetAttack() * 2;
		player->SetAttack(resultAttack);
		PrintFormatString("stat_setting_attack", { {"{Result}", to_string(resultAttack)} });
	}
	break;
	case 4:
	{
		int resultDefence = player->GetDefence() * 2;
		player->SetDefence(resultDefence);
		PrintFormatString("stat_setting_defence", { {"{Result}", to_string(resultDefence)} });
	}
	break;
	case 5:
		player->PrintStats();
		break;
	default:
		PrintString("invalid_input");
		break;
	}
}
