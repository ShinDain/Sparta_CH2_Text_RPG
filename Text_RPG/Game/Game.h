#pragma once
#include "../CommonInclude.h"
#include "../Character/Character.h"

class Game
{
public :
	enum class GameState
	{
		Create,
		Title,
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
	void LoopTitle();
	void ProcessInput_Title();

	void ProcessInput_Combat();

	void PrintCombatEnd();
private:
	bool mIsRunning;

	GameState mState;

	class Player* mPlayer;
	class Monster* mMonster;
};

