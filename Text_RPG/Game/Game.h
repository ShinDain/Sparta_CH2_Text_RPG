#pragma once
#include "../CommonInclude.h"
#include "../Character/Character.h"
#include <functional>

class Game
{
private:
	Game();
public:
	virtual ~Game();

	static Game& GetInstance();

	bool Initialize();
	
	void RunLoop();
	void ShutDown();

private:
	bool InitializeStringTable();
	bool InitializeStateManager();

	void ProcessStateManager();
private:
	bool mIsRunning;
};

