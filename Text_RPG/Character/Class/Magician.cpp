#include "Magician.h"

Magician::Magician(string name, int hp, int mp, int Attack, int defence)
	:Player(name, hp, mp, Attack, defence)
{
}

Magician::~Magician()
{
}

bool Magician::Initialize()
{
	bool result = Player::Initialize();

	mClass.Job = PlayerJob::Magician;
	mClass.Name = GetString("class_name_magician");
	mMP += 30;
	PrintString("class_selected_magician");

	return result;
}

void Magician::Attack(Character* target)
{
	PrintString("class_attack_magician");
	target->Hit(mAttack);
}
