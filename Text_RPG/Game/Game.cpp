#include "Game.h"
#include <iostream>
#include <vector>
#include "../System/FileLoader.h"
#include "../Character/Player.h"
#include "../Character/Class/Warrior.h"
#include "../Character/Class/Thief.h"
#include "../Character/Class/Magician.h"
#include "../Character/Class/Archer.h"

#include "../Character/Monster.h"

// State, Player, Monster, Map
// 정보를 가지고 게임 흐름을 조정
// 입력을 수신 후 전파
// 유한 상태 머신

Game::Game()
{
    mIsRunning = false;
    mPlayer = nullptr;

	mMonster = nullptr;

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
		case Game::GameState::Village:
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

	if (mMonster)
	{
		delete mMonster;
		mMonster = nullptr;
	}
}

bool Game::Initialize()
{
    //vector<string> fileStrings = {};
    //FileLoader::Load("C:\\Users\\Main\\Documents\\GitHub\\Sparta_CH2_Text_RPG\\Text_RPG\\Scripts\\TestScript.txt", fileStrings);
    //FileLoader::Load(".\\Scripts\\TestScript.txt", fileStrings);

    cout << "===========================================\n";
    cout << "   [ Dungeon Escape Text RPG ]\n";
    cout << "===========================================\n";

    bool result = true;

    cout << "용사의 이름을 입력해주세요 : ";
    string InName;
    cin >> InName;

    int hp = 0, mp = 0;
    while (hp < 50 || mp < 50)
    {
        cout << "HP와 MP를 입력해주세요 : ";
        cin >> hp >> mp;
        if (hp < 50 || mp < 50)
			cout << "HP 또는 MP가 너무 작습니다. 다시 입력해주세요. (50 이상)\n";
    }
	int attack = 0, defence = 0;
	while (attack <= 0 || defence <= 0)
	{
		cout << "공격력과 방어력을 입력해주세요 : ";
		cin >> attack >> defence;
		if(attack <= 0 || defence <= 0)
			cout << "공격력 또는 방어력이 너무 작습니다. 다시 입력해주세요. (1 이상)\n";
	}

	int selectClass = 0;
	while (selectClass <= 0 || selectClass > 4)
	{
		cout << "< 전직 시스템 > \n";
		cout << InName << "님, 직업을 선택해주세요!\n";
		cout << "1. 전사   2. 마법사   3. 도적   4. 궁수\n선택: ";
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
			cout << "잘못된 입력입니다. 다시 선택해주세요. \n";
			break;
		}
	}
    
    if (mPlayer)
    {
        result = mPlayer->Initialize();
        mPlayer->PrintStats();
		cout << "\nHP 포션 5개, MP 포션 5개가 기본 지급되었습니다.\n";

		ItemData hpPotionData("HPPotion", 50);
		ItemData mpPotionData("MPPotion", 50);
		
		mPlayer->AcquireItem(hpPotionData, 5);
		mPlayer->AcquireItem(mpPotionData, 5);
    }

	mMonster = new Monster("Slime", 30, 0, 20, 10);
	if (mMonster)
	{
		mMonster->Initialize();
	}
    
    mIsRunning = result;
	mState = GameState::Village;
    return result;
}

void Game::ProcessInput_Village()
{
	cout << "\n============= 마을 ===============\n";
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
		mState = GameState::Combat;
        break;
    case 1:
    {
        bool result = mPlayer->UseItem("HPPotion");
        if (!result)
            cout << "HPPotion이 부족합니다.\n";
		else
		{
			mPlayer->RecoveryHP(20);
		}
    }
        break;
    case 2:
    {
        bool result = mPlayer->UseItem("MPPotion");
        if (!result)
            cout << "MPPotion이 부족합니다.\n";		
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
	cout << "0. 마을로\n";
	cout << "1. 던전 입장\n";
	cout << "2. 인벤토리\n";
	cout << "3. 게임 종료\n";
	cout << "===================================\n";
	cout << "번호를 선택해주세요 : ";

	int input = 0;
	cin >> input;
	switch (input)
	{
	case 0:
		cout << "마을로 돌아갑니다.\n";
		mState = GameState::Village;
		break;
	case 1:
		cout << "다시 전투에 돌입합니다.\n";
		InitCombat();
		mState = GameState::Combat;
		break;
	case 2:
		mPlayer->PrintInventory();
		break;
	case 3:
		cout << "게임을 종료합니다.\n";
		mIsRunning = false;
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
		mPlayer->Attack(mMonster);
	}

	if (mMonster->IsAlive())
	{
		cout << "--- 몬스터 턴 ---\n";
		mMonster->Attack(mPlayer);
	}

	if (mPlayer->IsDead() || mMonster->IsDead())
	{
		mState = GameState::CombatEnd;
	}
}

void Game::PrintCombatEnd()
{
	if (mPlayer->IsAlive())
	{
		cout << "★ 전투 승리!\n";
		cout << "-> " << mMonster->GetName() << "의 " << mMonster->GetDropItemName() << " 획득!";
		mPlayer->AcquireItem(mMonster->GetDropItemData(), 1);
	}
	else
	{
		cout << "★ 전투 패배\n";
		cout << "";
		mIsRunning = false;
	}

	mState = GameState::MainMenu;
}

void Game::InitCombat()
{
	mMonster->Initialize();
}
