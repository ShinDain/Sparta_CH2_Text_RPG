#pragma once
#include "../CommonInclude.h"
#include "../Character/Character.h"
#include "../Character/Player.h"

class Game
{
public:
	Game();
	virtual ~Game();

	bool Initialize();
	void RunLoop();
	void ShutDown();

private:
	//void Update(float ElapsedTime);
	//void Render();
	void ProcessInput();
	
	void LoopTitle();
	void ProcessInput_Title(string input);

private:
	bool mIsRunning;
	bool mIsGameStarted;

	Player* mPlayer;
};

