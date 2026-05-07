#include "Game.h"
#include "../System/FileLoader.h"
#include "../System/Data/StringTable.h"
#include "../System/Data/ItemTable.h"
#include "../System/Data/MonsterTable.h"
#include "../Character/Player.h"
#include "../Character/Class/Warrior.h"
#include "../Character/Class/Thief.h"
#include "../Character/Class/Magician.h"
#include "../Character/Class/Archer.h"
#include "../Character/Monster.h"

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
		switch (mState)
		{
		case Game::GameState::SetStat:
			ProcessInput_Village();
			break;
		case Game::GameState::MainMenu:
			ProcessInput_MainMenu();
			break;
		case Game::GameState::Combat:
			ProcessInput_Combat();
			break;
		case Game::GameState::CombatEnd:
			PrintCombatEnd();
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
		PrintFormatString("acquire_basic_items",{
			{"{ItemName1}", HPpotionData->Name},
			{"{ItemAmount1}", to_string(5)},
			{"{ItemName2}", MPpotionData->Name},
			{"{ItemAmount2}", to_string(5)},
			});
		
		mPlayer->AcquireItem(HPpotionData, 5);
		mPlayer->AcquireItem(MPpotionData, 5);
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

	return result;
}

void Game::ProcessInput_Village()
{
	cout << "\n=========== 스탯 설정 =============\n";
	cout << "< 캐릭터 강화 >\n";
	cout << "1. HP UP    2. MP UP    3. 공격력 2배\n";
	cout << "4. 방어력 2배  5. 현재 능력치  0. 게임 시작\n";
	cout << "====================================\n";
	cout << "번호를 선택해주세요 : ";

	string input = {};
	cin >> input;

    int select = stoi(input);

    switch (select)
    {
    case 0:
        cout << "게임을 시작합니다.\n";
		mState = GameState::MainMenu;
        break;
    case 1:
    {
        bool result = mPlayer->UseItem("HP포션");
        if (!result)
            cout << "HP포션이 부족합니다.\n";
		else
		{
			mPlayer->RecoveryHP(20);
		}
    }
        break;
    case 2:
    {
        bool result = mPlayer->UseItem("MP포션");
        if (!result)
            cout << "MP포션이 부족합니다.\n";		
		else
		{
			mPlayer->RecoveryMP(20);
		}
    }
        break;
    case 3:
    {
        mPlayer->SetAttack(mPlayer->GetAttack() * 2);
        cout << "공격력이 2배가 되어 " << mPlayer->GetAttack() << "이 되었습니다.\n";
    }
        break;
    case 4:
    {
        mPlayer->SetDefence(mPlayer->GetDefence() * 2);
        cout << "방어력이 2배가 되어 " << mPlayer->GetDefence() << "이 되었습니다.\n";
    }
        break;
    case 5:
        mPlayer->PrintStats();
        break;
    default:
        cout << "잘못된 입력입니다.\n";
        break;
    }
}

void Game::ProcessInput_MainMenu()
{
	cout << "\n============= 메뉴 ===============\n";
	cout << "0. 게임 종료\n";
	cout << "1. 던전 입장\n";
	cout << "2. 인벤토리\n";
	cout << "3. 포션 제작소\n";
	cout << "4. 스탯 설정으로\n";
	cout << "===================================\n";
	cout << "번호를 선택해주세요 : ";

	int input = 0;
	cin >> input;
	switch (input)
	{
	case 0:
		cout << "게임을 종료합니다.\n";
		mIsRunning = false;

		break;
	case 1:
		cout << "전투에 돌입합니다.\n";
		InitCombat();
		cout << mMonster[mCurMonsterIdx]->GetName() << "과 만났습니다!\n";
		mState = GameState::Combat;
		break;
	case 2:
		mPlayer->PrintInventory();
		break;
	case 3:
		cout << "포션 제작소로 이동합니다.\n";
		mState = GameState::Alchemy;
		break;
	case 4:
		cout << "스탯 설정으로 돌아갑니다.\n";
		mState = GameState::SetStat;
		break;
	default:
		cout << "잘못된 입력입니다. 다시 입력해주세요.\n";
		break;
	}
}

void Game::ProcessInput_Combat()
{
	int input = -1;

	while (input != 1)
	{
		cout << "--- 플레이어 턴 ---\n";
		cout << "1. 공격\n";
		cout << "선택: ";
		cin >> input;
		if (input != 1)
		{
			cout << "잘못된 입력입니다.\n";
			continue;
		}
		mPlayer->Attack(mMonster[mCurMonsterIdx]);
	}

	if (mMonster[mCurMonsterIdx]->IsAlive())
	{
		cout << "--- 몬스터 턴 ---\n";
		mMonster[mCurMonsterIdx]->Attack(mPlayer);
	}

	if (mPlayer->IsDead() || mMonster[mCurMonsterIdx]->IsDead())
	{
		mState = GameState::CombatEnd;
	}
}

void Game::ProcessInput_Alchemy()
{
	cout << "\n=== 포션 제작소 ===\n";
	cout << "1. 전체 레시피 보기\n";
	cout << "2. 포션 이름으로 검색\n";
	cout << "3. 재료로 검색\n";
	cout << "4. 돌아가기\n";
	cout << "==================\n";
	cout << "번호를 선택해주세요 : ";

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
			cout << "검색할 포션 이름: ";
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
			cout << "검색할 재료 이름: ";
			string inputStr;
			cin >> inputStr;

			alchemyComp->FindRecipesByIngredient(inputStr);
		}
	}
		break;
	case 4:
		cout << "메뉴로 돌아갑니다.\n";
		mState = GameState::MainMenu;
		break;
	default:
		cout << "잘못된 입력입니다. 다시 입력해주세요.\n";
		break;
	}
}

void Game::PrintCombatEnd()
{
	if (mPlayer->IsAlive())
	{
		cout << "★ 전투 승리!\n";
		cout << "-> " << mMonster[mCurMonsterIdx]->GetName() << "의 " << mMonster[mCurMonsterIdx]->GetDropItemName() << " 획득!";

		const ItemData* dropItemData = FindItemDataByName(mMonster[mCurMonsterIdx]->GetDropItemName());
		mPlayer->AcquireItem(dropItemData, 1);
	}
	else
	{
		cout << "★ 전투 패배\n";
		cout << "";
		mIsRunning = false;
	}

	mCurMonsterIdx = (mCurMonsterIdx + 1) % 2;
	mState = GameState::MainMenu;
}

void Game::InitCombat()
{
	mMonster[mCurMonsterIdx]->Initialize();
}
