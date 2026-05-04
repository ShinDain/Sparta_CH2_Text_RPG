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

	Game mainGame;

	if (mainGame.Initialize())
	{
		mainGame.RunLoop();
	}
	mainGame.ShutDown();
}

//vector<string> fileStrings = {};
//FileLoader::Load("C:\\Users\\Main\\Documents\\GitHub\\Sparta_CH2_Text_RPG\\Text_RPG\\Scripts\\TestScript.txt", fileStrings);
//FileLoader::Load(".\\Scripts\\TestScript.txt", fileStrings);

// State, Player, Monster, Map
// 정보를 가지고 게임 흐름을 조정
// 입력을 수신 후 전파
// 유한 상태 머신
// Game에 구현되어 있는 각종 지저분한 함수 State로 분리

// 전체적으로 리터럴 없도록 정리
// 코드 정리

// 아이템 데이터를 스크립트로 분리,
// 게임 실행 시 로딩 과정을 통해 데이터 생성

// 스크립트로 분리할 내용
// 아이템 데이터
// 캐릭터 클래스 별 성장치
// 몬스터 데이터
// 레시피 데이터
// =======================

//