#include "Archer.h"

Archer::Archer(string name, int hp, int mp, int Attack, int defence)
	:Player(name, hp, mp, Attack, defence)
{
}

Archer::~Archer()
{
}

bool Archer::Initialize()
{
	bool result = Player::Initialize();

	mClass.Job = PlayerJob::Archer;
	mClass.Name = GetString("class_name_archer");
	mHP -= 10;
	mAttack += 20;
	PrintString("class_selected_archer");

	return result;
}

void Archer::Attack(Character* target)
{
	PrintString("class_attack_archer");
	target->Hit(mAttack);
}
