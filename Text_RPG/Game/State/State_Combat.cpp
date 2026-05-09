#include "State_Combat.h"
#include "../Conditions/TriggerCondition.h"

#include "../../Data/Table/StringTable.h"
#include "../../Manager/ObjectManager.h"
#include "../../Character/Character.h"

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

	Character* player = ObjectManager::GetInstance().mPlayer;
	Character* curMonster = nullptr;
	if (ObjectManager::GetInstance().mCurMonster)
		curMonster = ObjectManager::GetInstance().mMonster1;
	else
		curMonster = ObjectManager::GetInstance().mMonster2;

	while (input != 1)
	{
		PrintString("combat_player_select_1");
		PrintString("combat_player_select_2");
		PrintString("input_number");

		cin >> input;
		if (input != 1)
		{
			PrintString("invalid_input");
			continue;
		}
		player->Attack(curMonster);
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
