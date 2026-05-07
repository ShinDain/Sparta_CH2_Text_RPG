#include "Monster.h"
#include "Player.h"

Monster::Monster(const MonsterData* data)
	: mData(data)
{
	mName = mData->Name;
	mMaxHP = mData->HP;
	mHP = mData->HP;
	mMP = mData->MP;
	mAttack = mData->Attack;
	mDefence = mData->Defence;
	mDropItemName = mData->DropItemName;
}

Monster::~Monster()
{
}

bool Monster::Initialize()
{
	bool result = true;
	mIsDead = false;
	mHP = mMaxHP;

	return result;
}

void Monster::PrintStats()
{
	cout << "\n------------------------------------\n";
	cout << "닉네임: " << mName << " | Lv." << mLevel;
	cout << "\nHP: " << mHP << " | MP : " << mMP << " | 공격력: " << mAttack << " | 방어력 : " << mDefence << "\n";
	cout << "------------------------------------\n";
}

void Monster::Attack(Character* target)
{
	cout << "\"" << mName << "\"의 몸통박치기!";
	target->Hit(mAttack);
}

