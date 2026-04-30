// Text_RPG.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Game/Game.h"

int main()
{
	Game mainGame;

	if (mainGame.Initialize())
	{
		mainGame.RunLoop();
	}
	mainGame.ShutDown();
}
