#pragma once
#include "../Character/Character.h"

using namespace std;

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

private:
	bool mIsRunning;

	Character* mPlayer;
};

