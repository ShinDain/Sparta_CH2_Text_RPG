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
	//AddTransition<AlwaysTrueCondition>(StateID::SetStat);
	AddTransition<AlwaysTrueCondition>(StateID::MainMenu);
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

	int hp = 0, mp = 0;
	int attack = 0, defence = 0;
	
	/*cin >> InName;
	while (hp < 50 || mp < 50)
	{
		PrintString("input_stat_hp_mp");
		cin >> hp >> mp;
		if (hp < 50 || mp < 50)
		{
			PrintString("input_stat_hp_mp_error");
		}
	}
	while (attack <= 0 || defence <= 0)
	{
		PrintString("input_stat_attack_defence");
		cin >> attack >> defence;
		if (attack <= 0 || defence <= 0)
		{
			PrintString("input_stat_attack_defence_error");
		}
	}*/
	{
		cout << "기본 캐릭터로 자동 초기화 합니다." << endl;
		InName = "sdi";
		hp = 100, mp = 100;
		attack = 100, defence = 100;
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

		string hpPotionName = "HP포션";
		int hpPotionCnt = 5;
		string mpPotionName = "MP포션";
		int mpPotionCnt = 5;
		mainPlayer->AcquireItem(hpPotionName, hpPotionCnt);
		mainPlayer->AcquireItem(mpPotionName, mpPotionCnt);

		string bottleName = "공병";
		int bottleCnt = 5;
		mainPlayer->AcquireItem(bottleName, bottleCnt);

		PrintFormatString("acquire_basic_items", {
			{"{ItemName1}", hpPotionName},
			{"{ItemAmount1}", to_string(hpPotionCnt)},
			{"{ItemName2}", mpPotionName},
			{"{ItemAmount2}", to_string(mpPotionCnt)},
			});
	}

	string slimeName = "슬라임";
	string mushroomName = "주황 버섯";
	string oakName = "오크";
	string dragonName = "드래곤";
	const MonsterData* slimeData = FindMonsterDataByName(slimeName);
	const MonsterData* mushroomData = FindMonsterDataByName(mushroomName);
	const MonsterData* oakData = FindMonsterDataByName(oakName);
	const MonsterData* dragonData = FindMonsterDataByName(dragonName);

	Monster* monster1 = nullptr;
	Monster* monster2 = nullptr;
	Monster* monster3 = nullptr;
	Monster* monster4 = nullptr;

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
	monster3 = objManager.CreateObject<Monster>(oakData);
	if (monster3)
	{
		monster3->Initialize();
	}
	monster4 = objManager.CreateObject<Monster>(dragonData);
	if (monster4)
	{
		monster4->Initialize();
	}

	// 테스트 코드
	objManager.mPlayer = mainPlayer;
	objManager.mMonster1 = monster1;
	objManager.mMonster2 = monster2;
	objManager.mMonster3 = monster3;
	objManager.mMonster4 = monster4;
}
