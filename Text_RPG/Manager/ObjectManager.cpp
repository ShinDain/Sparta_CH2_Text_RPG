#include "ObjectManager.h"

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
}
