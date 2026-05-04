#include "Monster.h"
#include "Player.h"

Monster::Monster(string name, int hp, int mp, int Attack, int defence)
	: Character(name, hp, mp, Attack, defence)
{
	mDropItemName = "끈적한 젤리";
}

Monster::~Monster()
{
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

