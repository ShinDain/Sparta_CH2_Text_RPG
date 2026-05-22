// Text_RPG.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdlib.h>
#include <crtdbg.h>
#include "Game/Game.h"

int main()
{
	// 프로그램 종료 시 메모리 누수 리포트 출력 설정
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	// test
	Game& mainGame = Game::GetInstance();

	if (mainGame.Initialize())
	{
		mainGame.RunLoop();
	}
	mainGame.ShutDown();
}
