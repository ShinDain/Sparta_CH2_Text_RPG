#include "ObjectManager.h"
#include "../Character/Monster/Monster.h"
#include "../Game/Game.h"

ObjectManager& ObjectManager::GetInstance()
{
	static ObjectManager Instance;
	return Instance;
}


ObjectManager::~ObjectManager()
{
	for (Character* object : mObjects)
	{
		delete object;
	}

	mObjects.clear();

	// 테스트 코드
	mPlayer = nullptr;
	mMonster1 = nullptr;
	mMonster2 = nullptr;
	mMonster3 = nullptr;
	mMonster4 = nullptr;
}


Monster* ObjectManager::GetCurrentMonster()
{
	Monster* curMonster = nullptr;

	switch (mCurMonster)
	{
	case 0:
		curMonster = mMonster1;
		break;
	case 1:
		curMonster = mMonster2;
		break;
	case 2:
		curMonster = mMonster3;
		break;
	case 3:
		curMonster = mMonster4;
		break;
	default:
		break;
	}

    return curMonster;
}

int ObjectManager::NextMonster()
{
	mCurMonster += 1;
	if(mCurMonster >= 4)
	{
		Game::GetInstance().SetGameEnd(true);
	}

	return mCurMonster;
}
