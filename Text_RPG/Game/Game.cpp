#include "Game.h"
#include <iostream>
#include <vector>
#include "../System/FileLoader.h"

// State, Player, Monster, Map
// 정보를 가지고 게임 흐름을 조정
// 입력을 수신 후 전파
// 유한 상태 머신


Game::Game()
{
    mIsRunning = false;
    mIsGameStarted = false;
    mPlayer = nullptr;
}

Game::~Game()
{
}

void Game::RunLoop()
{
    //while (mIsRunning)
    {
        LoopTitle();
        ProcessInput();
    }
}

void Game::ShutDown()
{
    if (mPlayer)
    {
        delete mPlayer;
        mPlayer = nullptr;
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
    mPlayer = new Character();
    if (mPlayer)
    {
        result = mPlayer->Initialize();
        mPlayer->PrintStats();
    }

    cout << "\nHP 포션 5개, MP 포션 5개가 기본 지급되었습니다.\n";

    mPlayer->AcquireItem("HPPotion", 5);
    mPlayer->AcquireItem("MPPotion", 5);

    mIsRunning = result;
    return result;
}

void Game::ProcessInput()
{
    string input = {};
    cin >> input;

    if (input == "quit")
    {
        mIsRunning = false;
    }
    else if (input == "print")
    {
        mPlayer->PrintStats();
    }

    ProcessInput_Title(input);
}

void Game::LoopTitle()
{
    //while (true)
    {
        cout << "\n============================================\n";
        cout << "< 캐릭터 강화 >\n";
        cout << "1. HP UP    2. MP UP    3. 공격력 2배\n";
        cout << "2. 방어력 2배  5. 현재 능력치  0. 게임 시작\n";
        cout << "============================================\n";
        cout << "번호를 선택해주세요 : ";
    }
}

void Game::ProcessInput_Title(string input)
{
    int select = stoi(input);

    switch (select)
    {
    case 0:
        mIsGameStarted = true;
        cout << "게임 시작";
        break;
    case 1:
    {
        bool result = mPlayer->UseItem("HPPotion");
        if (!result)
            cout << "HPPotion이 부족합니다.";
    }
        break;
    case 2:
    {
        bool result = mPlayer->UseItem("MPPotion");
        if (!result)
            cout << "MPPotion이 부족합니다.";
    }
        break;
    default:
        cout << "잘못된 입력입니다.";
        break;
    }

}
