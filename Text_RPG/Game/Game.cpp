#include "Game.h"
#include <iostream>
#include <tchar.h>

Game::Game()
{
    mIsRunning = false;
    Player = nullptr;
}

Game::~Game()
{
}

void Game::RunLoop()
{
    while (mIsRunning)
    {
        ProcessInput();
    }
}

void Game::ShutDown()
{
    if (Player)
    {
        delete Player;
        Player = nullptr;
    }
}

bool Game::Initialize()
{
    cout << "===========================================\n";
    cout << "   [ Dungeon Escape Text RPG ]\n";
    cout << "===========================================\n";
    cout << "Enter your hero's name : ";

    Player = new Character();
    string playerName;
    
    cin >> playerName;
    Player->SetName(playerName);
    
    mIsRunning = true;

    return true;
}

void Game::ProcessInput()
{
    string Input = {};
    cin >> Input;

    cout << "Input is " << Input << "\n";
    cout << "Your name is " << Player->GetName() << "\n";

    if (Input == "quit")
    {
        mIsRunning = false;
    }
}
