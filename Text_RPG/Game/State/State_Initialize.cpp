#include "State_Initialize.h"
#include "../../Manager/StateManager.h"
#include "../Conditions/AlwaysTrueCondition.h"

#include "../../Data/Table/StringTable.h"
#include "../../Data/Table/ItemTable.h"
#include "../../Data/Table/MonsterTable.h"

#include "../../Character/Player.h"
#include "../../Character/Class/Warrior.h"
#include "../../Character/Class/Thief.h"
#include "../../Character/Class/Magician.h"
#include "../../Character/Class/Archer.h"
#include "../../Character/Monster/Monster.h"

#include "../../Manager/ObjectManager.h"


State_Initialize::State_Initialize()
{
	mName = "Initialize";
	AddTransition<AlwaysTrueCondition>(StateID::SetStat);
}

void State_Initialize::Enter()
{
}

void State_Initialize::Process()
{
	ObjectManager& objManager = ObjectManager::GetInstance();

	PrintString("double_line");
	PrintString("title_name");
	PrintString("double_line");

	PrintString("input_name");
	string InName;
	cin >> InName;

	int hp = 0, mp = 0;
	while (hp < 50 || mp < 50)
	{
		PrintString("input_stat_hp_mp");
		cin >> hp >> mp;
		if (hp < 50 || mp < 50)
		{
			PrintString("input_stat_hp_mp_error");
		}
	}
	int attack = 0, defence = 0;
	while (attack <= 0 || defence <= 0)
	{
		PrintString("input_stat_attack_defence");
		cin >> attack >> defence;
		if (attack <= 0 || defence <= 0)
		{
			PrintString("input_stat_attack_defence_error");
		}
	}

	int selectClass = 0;
	Player* mainPlayer = nullptr;
	while (selectClass <= 0 || selectClass > 4)
	{
		PrintString("class_select_1");
		PrintFormatString("class_select_2", { {"{Name}", InName} });
		PrintString("class_select_3");
		cin >> selectClass;
		switch (selectClass)
		{
		case 1:
			mainPlayer = objManager.CreateObject<Warrior>(InName, hp, mp, attack, defence);
			break;
		case 2:
			mainPlayer = objManager.CreateObject<Magician>(InName, hp, mp, attack, defence);
			break;
		case 3:
			mainPlayer = objManager.CreateObject<Thief>(InName, hp, mp, attack, defence);
			break;
		case 4:
			mainPlayer = objManager.CreateObject<Archer>(InName, hp, mp, attack, defence);
			break;
		default:
			PrintString("invalid_input");
			break;
		}
	}

	if (mainPlayer)
	{
		bool result = true;
		mainPlayer->PrintStats();

		const ItemData* HPpotionData = FindItemDataByName("HP포션");
		const ItemData* MPpotionData = FindItemDataByName("MP포션");

		mainPlayer->AcquireItem(HPpotionData, 5);
		mainPlayer->AcquireItem(MPpotionData, 5);

		PrintFormatString("acquire_basic_items", {
			{"{ItemName1}", HPpotionData->Name},
			{"{ItemAmount1}", to_string(5)},
			{"{ItemName2}", MPpotionData->Name},
			{"{ItemAmount2}", to_string(5)},
			});
	}

	const MonsterData* slimeData = FindMonsterDataByName("슬라임");
	const MonsterData* mushroomData = FindMonsterDataByName("주황 버섯");

	Monster* monster1 = nullptr;
	Monster* monster2 = nullptr;

	monster1 = objManager.CreateObject<Monster>(slimeData);
	if (monster1)
	{
		monster1->Initialize();
	}
	monster2 = objManager.CreateObject<Monster>(mushroomData);
	if (monster2)
	{
		monster2->Initialize();
	}

	// 테스트 코드
	objManager.mPlayer = mainPlayer;
	objManager.mMonster1 = monster1;
	objManager.mMonster2 = monster2;
}
