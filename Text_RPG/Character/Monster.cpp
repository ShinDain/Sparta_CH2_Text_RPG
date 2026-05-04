#include "Monster.h"
#include "Player.h"

Monster::Monster(string name, int hp, int mp, int Attack, int defence)
	: Character(name, hp, mp, Attack, defence)
{
	ItemData dropItemData("끈적한 젤리", 30);
	mDropItemData = dropItemData;
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

