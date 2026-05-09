#include "State_CombatEnd.h"
#include "../Conditions/AlwaysTrueCondition.h"

#include "../Game.h"
#include "../../Data/Table/StringTable.h"
#include "../../Data/Table/ItemTable.h"
#include "../../Manager/ObjectManager.h"
#include "../../Character/Monster/Monster.h"
#include "../../Character/Player.h"


State_CombatEnd::State_CombatEnd()
{
	mName = "CombatEnd";
	AddTransition<AlwaysTrueCondition>(StateID::MainMenu);
}

void State_CombatEnd::Enter()
{
}

void State_CombatEnd::Process()
{
	Player* player = dynamic_cast<Player*>(ObjectManager::GetInstance().mPlayer);
	Monster* curMonster = nullptr;
	if (ObjectManager::GetInstance().mCurMonster)
		curMonster = dynamic_cast<Monster*>(ObjectManager::GetInstance().mMonster1);
	else
		curMonster = dynamic_cast<Monster*>(ObjectManager::GetInstance().mMonster2);

	if (player->IsAlive())
	{
		PrintString("combat_end_win");
		string monsterName = curMonster->GetName();

		string dropItemName = curMonster->GetDropItemName();
		const ItemData* dropItemData = FindItemDataByName(curMonster->GetDropItemName());
		player->AcquireItem(dropItemData, 1);
		PrintFormatString("combat_end_result_item", { {"{MonsterName}",  monsterName}, {"{DropItemName}", dropItemName} });

		int gainExp = curMonster->GetRewardExp(player->GetLevel());
		player->GainEXP(gainExp);
	}
	else
	{
		PrintString("combat_end_defeat");
		Game::GetInstance().ShutDown();
	}

	ObjectManager::GetInstance().mCurMonster = !ObjectManager::GetInstance().mCurMonster;
}
