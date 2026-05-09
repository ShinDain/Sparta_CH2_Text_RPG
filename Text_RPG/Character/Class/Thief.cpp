#include "Thief.h"

Thief::Thief(string name, int hp, int mp, int Attack, int defence)
	:Player(name, hp, mp, Attack, defence)
{
}

Thief::~Thief()
{
}

bool Thief::Initialize()
{
	bool result = Player::Initialize();

	mClass.Job = PlayerJob::Thief;
	mClass.Name = GetString("class_name_thief");
	mMP += 20;
	mAttack += 10;
	PrintString("class_selected_thief");

	return result;
}

void Thief::Attack(Character* target)
{
	int attackCnt = 5;
	int resultDamage = mAttack / attackCnt;

	for (int i = 0; i < attackCnt; ++i)
	{
		PrintString("class_attack_thief");
		target->Hit(resultDamage);
	}
}
