#include "Warrior.h"

Warrior::Warrior(string name, int hp, int mp, int Attack, int defence)
	:Player(name, hp, mp, Attack, defence)
{
}

Warrior::~Warrior()
{
}

bool Warrior::Initialize()
{
	bool result = Player::Initialize();

	mClass.Job = PlayerJob::Warrior;
	mClass.Name = GetString("class_name_warrior");
	mHP += 20;
	mDefence += 10;
	PrintString("class_selected_warrior");

	return result;
}

void Warrior::Attack(Character* target)
{
	PrintString("class_attack_warrior");
	target->Hit(mAttack);
}
