#include "Game.h"
#include "../Data/FileLoader.h"
#include "../Data/Table/StringTable.h"
#include "../Data/Table/ItemTable.h"
#include "../Data/Table/MonsterTable.h"
#include "../Data/Table/LevelDataTable.h"
#include "../Manager/StateManager.h"

#include "../Character/Player.h"
#include "../Character/Monster/Monster.h"
#include "../Component/AlchemyComponent.h"

#include <random>

const string INIT_FILE_PATH = ".\\Scripts\\FilePaths.txt";

Game::Game()
{
    mIsRunning = false;
}

Game::~Game()
{
}

Game& Game::GetInstance()
{
	static Game Instance;
	return Instance;
}

void Game::RunLoop()
{
    while (mIsRunning)
    {
		ProcessStateManager();
    }
}

void Game::ShutDown()
{
	mIsRunning = false;
}

bool Game::Initialize()
{
    bool result = true;
	if (!InitializeStringTable())
		return false;

	if (!InitializeStateManager())
		return false;
    
    mIsRunning = result;
	//mState = GameState::SetStat;
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
