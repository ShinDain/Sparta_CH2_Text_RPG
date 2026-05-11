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

	Game& mainGame = Game::GetInstance();

	if (mainGame.Initialize())
	{
		mainGame.RunLoop();
	}
	mainGame.ShutDown();
}

// State, Player, Monster, Map
// 정보를 가지고 게임 흐름을 조정
// 입력을 수신 후 전파
// 유한 상태 머신
// Game에 구현되어 있는 각종 지저분한 함수 State로 분리

// 스크립트로 분리할 내용
// 캐릭터 클래스 별 성장치
// 레시피 데이터
// =======================
