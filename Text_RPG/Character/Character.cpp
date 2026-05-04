#include "Character.h"
#include <iostream>
#include "Player.h"

Character::Character(string name, int hp, int mp, int Attack, int defence)
	:mName(name), mHP(hp), mMP(mp), mAttack(Attack), mDefence(defence), mLevel(1)
{
	mIsDead = false;
}

Character::~Character()
{
}

bool Character::Initialize()
{
	bool result = true;

	return result;
}

void Character::PrintStats()
{
	cout << "\n====================================\n";
	cout << mName << " 의 현재 능력치\n";
	cout << "====================================\n";
	cout << "HP: " << mHP << "    MP : " << mMP << "\n";
	cout << "공격력: " << mAttack << "    방어력 : " << mDefence << "\n";
	cout << "====================================\n";
}

void Character::RecoveryHP(int amount)
{
	mHP += amount;

	cout << "HP포션을 사용하여, HP를 20만큼 회복하였습니다.\n";
}

void Character::RecoveryMP(int amount)
{
	mMP += amount;

	cout << "MP포션을 사용하여, MP를 20만큼 회복하였습니다.\n";
}

void Character::Hit(int damage)
{
	int resultDamage = max((damage - mDefence), 1);
	int preHP = mHP;
	int postHP = mHP - resultDamage;
	mHP = max(postHP, 0);

	cout << mName << "에게 " << resultDamage << "데미지!\n";
	cout << mName << " HP: " << preHP << " -> " << postHP;
	if (postHP <= 0)
	{
		cout << " (사망)\n";
		mIsDead = true;
	}
	else
	{
		cout << endl;
	}
}
