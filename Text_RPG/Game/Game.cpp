#include "Game.h"
#include "../System/FileLoader.h"
#include "../System/Data/StringTable.h"
#include "../System/Data/ItemTable.h"
#include "../System/Data/MonsterTable.h"
#include "../System/Data/LevelDataTable.h"
#include "../Game/StateManager.h"

#include "../Character/Player.h"
#include "../Character/Class/Warrior.h"
#include "../Character/Class/Thief.h"
#include "../Character/Class/Magician.h"
#include "../Character/Class/Archer.h"
#include "../Character/Monster/Monster.h"

#include "../Component/AlchemyComponent.h"

#include <random>

const string INIT_FILE_PATH = ".\\Scripts\\FilePaths.txt";

Game::Game()
{
    mIsRunning = false;
    mPlayer = nullptr;

	mMonster[0] = nullptr;
	mMonster[1] = nullptr;

	mCurMonsterIdx = 0;

	mState = GameState::Create;
}

Game::~Game()
{
}

void Game::RunLoop()
{
    while (mIsRunning)
    {
		ProcessStateManager();

		switch (mState)
		{
		case Game::GameState::SetStat:
			ProcessInput_SetStat();
			break;
		case Game::GameState::MainMenu:
			ProcessInput_MainMenu();
			break;
		case Game::GameState::Combat:
			ProcessInput_Combat();
			break;
		case Game::GameState::CombatEnd:
			ProcessCombatEnd();
			break;
		case Game::GameState::Alchemy:
			ProcessInput_Alchemy();
			break;
		case Game::GameState::None:
			break;
		default:
			break;
		}
    }
}

void Game::ShutDown()
{
    if (mPlayer)
    {
        delete mPlayer;
        mPlayer = nullptr;
    }

	if (mMonster[0])
	{
		delete mMonster[0];
		mMonster[0] = nullptr;
	}
	if (mMonster[1])
	{
		delete mMonster[1];
		mMonster[1] = nullptr;
	}
}

bool Game::Initialize()
{
    bool result = true;
	if (!InitializeStringTable())
		return false;

	if (!InitializeStateManager())
		return false;

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
	while (selectClass <= 0 || selectClass > 4)
	{
		PrintString("class_select_1");
		PrintFormatString("class_select_2", { {"{Name}", InName} });
		PrintString("class_select_3");
		cin >> selectClass;
		switch (selectClass)
		{
		case 1:
			mPlayer = new Warrior(InName, hp, mp, attack, defence);
			break;
		case 2:
			mPlayer = new Magician(InName, hp, mp, attack, defence);
			break;
		case 3:
			mPlayer = new Thief(InName, hp, mp, attack, defence);
			break;
		case 4:
			mPlayer = new Archer(InName, hp, mp, attack, defence);
			break;
		default:
			PrintString("invalid_input");
			break;
		}
	}
    
    if (mPlayer)
    {
        result = mPlayer->Initialize();
        mPlayer->PrintStats();

		const ItemData* HPpotionData = FindItemDataByName("HP포션");
		const ItemData* MPpotionData = FindItemDataByName("MP포션");

		mPlayer->AcquireItem(HPpotionData, 5);
		mPlayer->AcquireItem(MPpotionData, 5);

		PrintFormatString("acquire_basic_items",{
			{"{ItemName1}", HPpotionData->Name},
			{"{ItemAmount1}", to_string(5)},
			{"{ItemName2}", MPpotionData->Name},
			{"{ItemAmount2}", to_string(5)},
			});
    }

	const MonsterData* slimeData = FindMonsterDataByName("슬라임");
	const MonsterData* mushroomData = FindMonsterDataByName("주황 버섯");

	mMonster[0] = new Monster(slimeData);
	if (mMonster[0])
	{
		mMonster[0]->Initialize();
	}
	mMonster[1] = new Monster(mushroomData);
	if (mMonster[1])
	{
		mMonster[1]->Initialize();
	}
    
    mIsRunning = result;
	mState = GameState::SetStat;
    return result;
}

bool Game::InitializeStringTable()
{
	vector<string> filePaths = {};
	FileLoader::Load(INIT_FILE_PATH, filePaths);

	bool result = true;

	{
		StringTable& table = StringTable::GetInstance();
		result = table.Load(filePaths[0]);
	}

	{
		ItemTable& table = ItemTable::GetInstance();
		result = table.Load(filePaths[1]);
	}

	{
		MonsterTable& table = MonsterTable::GetInstance();
		result = table.Load(filePaths[2]);
	}

	{
		LevelDataTable& table = LevelDataTable::GetInstance();
		result = table.Load(filePaths[3]);
	}

	return result;
}

bool Game::InitializeStateManager()
{
	return StateManager::GetInstance().Initialize();
}

void Game::ProcessStateManager()
{
	StateManager::GetInstance().Process();
}

void Game::ProcessInput_SetStat()
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

    switch (select)
    {
    case 0:
		PrintString("game_start");
		mState = GameState::MainMenu;
        break;
    case 1:
    {
		string itemName = "HP포션";
        bool result = mPlayer->UseItem(itemName);
		if (!result)
		{
			PrintFormatString("item_use_not_enough", { {"ItemName}", itemName} });
		}
		else
		{
			mPlayer->RecoveryHP(20, itemName);
		}
    }
        break;
	case 2:
	{
		string itemName = "MP포션";
		bool result = mPlayer->UseItem(itemName);
		if (!result)
		{
			PrintFormatString("item_use_not_enough", { {"ItemName}", itemName} });
		}
		else
		{
			mPlayer->RecoveryMP(20, itemName);
		}
    }
        break;
    case 3:
    {
		int resultAttack = mPlayer->GetAttack() * 2;
        mPlayer->SetAttack(resultAttack);
		PrintFormatString("stat_setting_attack", { {"{Result}", to_string(resultAttack)} });
    }
        break;
    case 4:
    {
		int resultDefence = mPlayer->GetDefence() * 2;
        mPlayer->SetDefence(resultDefence);
		PrintFormatString("stat_setting_defence", { {"{Result}", to_string(resultDefence)} });
    }
        break;
    case 5:
        mPlayer->PrintStats();
        break;
    default:
		PrintString("invalid_input");
        break;
    }
}

void Game::ProcessInput_MainMenu()
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
	switch (input)
	{
	case 0:
		PrintString("game_exit");
		mIsRunning = false;

		break;
	case 1:
		PrintString("combat_start");
		InitCombat();
		PrintFormatString("combat_encounter", { {"{Name}", mMonster[mCurMonsterIdx]->GetName()} });
		mState = GameState::Combat;
		break;
	case 2:
		mPlayer->PrintInventory();
		break;
	case 3:
		PrintString("menu_move_alchemy");
		mState = GameState::Alchemy;
		break;
	case 4:
		mPlayer->PrintStats();
		break;
	case 5:
		PrintString("menu_move_stat");
		mState = GameState::SetStat;
		break;
	default:
		PrintString("invalid_input");
		break;
	}
}

void Game::ProcessInput_Combat()
{
	int input = -1;

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
		mPlayer->Attack(mMonster[mCurMonsterIdx]);
	}

	if (mMonster[mCurMonsterIdx]->IsAlive())
	{
		PrintString("combat_monster");
		mMonster[mCurMonsterIdx]->Attack(mPlayer);
	}

	if (mPlayer->IsDead() || mMonster[mCurMonsterIdx]->IsDead())
	{
		mState = GameState::CombatEnd;
	}
}

void Game::ProcessInput_Alchemy()
{
	PrintString("alchemy_select_1");
	PrintString("alchemy_select_2");
	PrintString("alchemy_select_3");
	PrintString("alchemy_select_4");
	PrintString("alchemy_select_5");
	PrintString("double_line");
	PrintString("input_number");

	int input = 0;
	cin >> input;
	switch (input)
	{
	case 1:
	{
		AlchemyComponent* alchemyComp = mPlayer->FindComponent<AlchemyComponent>("Alchemy");
		if (alchemyComp)
		{
			alchemyComp->PrintAllRecipes();
		}
	}
		break;
	case 2:
	{
		AlchemyComponent* alchemyComp = mPlayer->FindComponent<AlchemyComponent>("Alchemy");
		if (alchemyComp)
		{
			PrintString("alchemy_find_by_potion");
			string inputStr;
			cin >> inputStr;

			alchemyComp->FindRecipesByResult(inputStr);
		}
		break;
	}
	case 3:
	{
		AlchemyComponent* alchemyComp = mPlayer->FindComponent<AlchemyComponent>("Alchemy");
		if (alchemyComp)
		{
			PrintString("alchemy_find_by_ingredient");
			string inputStr;
			cin >> inputStr;

			alchemyComp->FindRecipesByIngredient(inputStr);
		}
	}
		break;
	case 4:
		PrintString("alchemy_move_menu");
		mState = GameState::MainMenu;
		break;
	default:
		PrintString("invalid_input");
		break;
	}
}

void Game::ProcessCombatEnd()
{
	if (mPlayer->IsAlive())
	{
		PrintString("combat_end_win");
		string monsterName = mMonster[mCurMonsterIdx]->GetName();

		string dropItemName = mMonster[mCurMonsterIdx]->GetDropItemName();
		const ItemData* dropItemData = FindItemDataByName(mMonster[mCurMonsterIdx]->GetDropItemName());
		mPlayer->AcquireItem(dropItemData, 1);
		PrintFormatString("combat_end_result_item", { {"{MonsterName}",  monsterName}, {"{DropItemName}", dropItemName} });

		int gainExp = mMonster[mCurMonsterIdx]->GetRewardExp(mPlayer->GetLevel());
		mPlayer->GainEXP(gainExp);
	}
	else
	{
		PrintString("combat_end_defeat");
		mIsRunning = false;
	}

	mCurMonsterIdx = (mCurMonsterIdx + 1) % 2;
	mState = GameState::MainMenu;
}

void Game::InitCombat()
{
	mMonster[mCurMonsterIdx]->Initialize();
}
