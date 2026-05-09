#pragma once
#include "../CommonInclude.h"
#include "../Character/Character.h"
#include <functional>

class Game
{
public :
	enum class GameState
	{
		Create,
		SetStat,
		MainMenu,
		Combat,
		CombatEnd,
		Alchemy,
		None,
	};

public:
	Game();
	virtual ~Game();

	bool Initialize();
	
	void RunLoop();
	void ShutDown();

private:
	bool InitializeStringTable();
	bool InitializeStateManager();

	void ProcessStateManager();

	void ProcessInput_SetStat();
	void ProcessInput_MainMenu();
	void ProcessInput_Combat();
	void ProcessInput_Alchemy();

	void ProcessCombatEnd();

	void InitCombat();
private:
	bool mIsRunning;

	GameState mState;

	class Player* mPlayer;
	class Monster* mMonster[2];

	int mCurMonsterIdx;
};

