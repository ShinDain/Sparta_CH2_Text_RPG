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
		Village,
		MainMenu,
		Combat,
		CombatEnd,
		None,
	};

public:
	Game();
	virtual ~Game();

	bool Initialize();
	void RunLoop();
	void ShutDown();

private:
	void ProcessInput_Village();
	void ProcessInput_MainMenu();
	void ProcessInput_Combat();

	void PrintCombatEnd();

	void InitCombat();
private:
	bool mIsRunning;

	GameState mState;

	class Player* mPlayer;
	class Monster* mMonster;
};

