#include "Game.h"
#include <iostream>
#include <tchar.h>

Game::Game()
{
    mIsRunning = false;
    mPlayer = nullptr;
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
    if (mPlayer)
    {
        delete mPlayer;
        mPlayer = nullptr;
    }
}

bool Game::Initialize()
{
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

    mIsRunning = result;
    return result;
}

void Game::ProcessInput()
{
    string Input = {};
    cin >> Input;

    if (Input == "quit")
    {
        mIsRunning = false;
    }
    else if (Input == "print")
    {
        mPlayer->PrintStats();
    }
}
