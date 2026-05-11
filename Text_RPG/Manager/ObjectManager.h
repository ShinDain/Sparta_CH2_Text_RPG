#pragma once
#include "../CommonInclude.h"
#include "../Character/Character.h"

class Monster;
class Player;

class ObjectManager
{
private:
	ObjectManager() {};
public:
	~ObjectManager();
	static ObjectManager& GetInstance();

	template<typename T, typename... Args>
	T* CreateObject(Args&&... args);

	// 테스트를 위한 임시 변수
	Player* mPlayer;
	Monster* mMonster1;
	Monster* mMonster2;
	Monster* mMonster3;
	Monster* mMonster4;
	int mCurMonster = 0;
	//

	Monster* GetCurrentMonster();
	int NextMonster();

private:
	vector<Character*> mObjects;
};

template<typename T, typename... Args>
inline T* ObjectManager::CreateObject(Args&&... args)
{
	static_assert(is_base_of<Character, T>::value, "Character를 상속받은 객체만 생성 가능합니다.");

	T* newObject = new T(forward<Args>(args)...);

	mObjects.push_back(newObject);
	if (newObject)
	{
		newObject->Initialize();
	}

	return newObject;
}
