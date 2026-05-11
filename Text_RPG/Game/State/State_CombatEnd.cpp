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
	Game::GetInstance().SetPotionStock();
}

void State_CombatEnd::Process()
{
	Player* player = ObjectManager::GetInstance().mPlayer;
	Monster* curMonster = ObjectManager::GetInstance().GetCurrentMonster();

	if (player->IsAlive())
	{
		PrintString("combat_end_win");
		string monsterName = curMonster->GetName();

		string dropItemName = curMonster->GetDropItemName();
		
		player->AcquireItem(dropItemName, 1);
		PrintFormatString("combat_end_result_item", { {"{MonsterName}",  monsterName}, {"{DropItemName}", dropItemName} });

		int gainExp = curMonster->GetRewardExp(player->GetLevel());
		player->GainEXP(gainExp);
	}
	else
	{
		PrintString("combat_end_defeat");
		Game::GetInstance().ShutDown();
	}

	int nextMonsterIdx = ObjectManager::GetInstance().NextMonster();

	if (nextMonsterIdx == 3)
	{
		cout << "보스방이 개방되었습니다. 준비를 확실히 하세요." << endl;
		cout << "보스 드래곤 등장! (HP 200, 공격력 60, 방어력 20)" << endl;
	}
}
