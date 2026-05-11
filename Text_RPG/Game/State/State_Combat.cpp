#include "State_Combat.h"
#include "../Conditions/TriggerCondition.h"

#include "../../Data/Table/StringTable.h"
#include "../../Manager/ObjectManager.h"
#include "../../Character/Player.h"
#include "../../Character/Monster/Monster.h"

State_Combat::State_Combat()
{
	mName = "Combat";
	AddTransition<TriggerCondition>(StateID::CombatEnd);
}

void State_Combat::Enter()
{
	PrintString("combat_start");
	Character* curMonster = nullptr;
	if (ObjectManager::GetInstance().mCurMonster)
		curMonster = ObjectManager::GetInstance().mMonster1;
	else
		curMonster = ObjectManager::GetInstance().mMonster2;
	
	if (curMonster)
	{
		PrintFormatString("combat_encounter", { {"{Name}", curMonster->GetName()} });
		curMonster->Initialize();
	}
}

void State_Combat::Process()
{
	int input = -1;

	Player* player = dynamic_cast<Player*>(ObjectManager::GetInstance().mPlayer);
	Monster* curMonster = nullptr;
	if (ObjectManager::GetInstance().mCurMonster)
		curMonster = dynamic_cast<Monster*>(ObjectManager::GetInstance().mMonster1);
	else
		curMonster = dynamic_cast<Monster*>(ObjectManager::GetInstance().mMonster2);

	bool bAction = true;
	while (bAction)
	{
		bAction = false;

		PrintString("combat_player_select_1");
		PrintString("combat_player_select_2");
		PrintString("combat_player_select_3");
		PrintString("input_number");

		cin >> input;

		switch (input)
		{
		case 1 :
			Action_Attack(player, curMonster);
			break;
		case 2 :
			Action_Item(player);
			break;
		default:
			PrintString("invalid_input");
			bAction = true;
			break;
		}
	}

	if (curMonster->IsAlive())
	{
		PrintString("combat_monster");
		curMonster->Attack(player);
	}

	if (player->IsDead() || curMonster->IsDead())
	{
		mTransitions[StateID::CombatEnd]->Notify();
	}
}

void State_Combat::Action_Attack(Player* player, Monster* target)
{
	player->Attack(target);
	return;
}

void State_Combat::Action_Item(Player* player)
{
	bool bAction = true;
	while (bAction)
	{
		bAction = false;

		// 테스트 코드
		// 실제 가지고 있는 아이템 기반의 리스트 제공 필요
		PrintString("combat_inventory_select_1");
		PrintString("combat_inventory_select_2");
		PrintString("combat_inventory_select_3");
		PrintString("combat_input_item");

		string input = {};
		cin >> input;

		int select = stoi(input);

		Player* player = dynamic_cast<Player*>(ObjectManager::GetInstance().mPlayer);

		switch (select)
		{
		case 1:
		{
			string itemName = "HP포션";
			bool result = player->UseItem(itemName);
			if (!result)
			{
				PrintFormatString("item_use_not_enough", { {"ItemName}", itemName} });
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
				PrintFormatString("item_use_not_enough", { {"ItemName}", itemName} });
			}
			else
			{
				player->RecoveryMP(20, itemName);
			}
		}
		break;
		default:
			PrintString("invalid_input");
			bAction = true;
			break;
		}
	}
}
