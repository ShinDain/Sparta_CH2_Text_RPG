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
	mClass.Name = "마법사";
	mMP += 30;
	cout << "마법사로 전직하였습니다! (MP + 30)\n";

	return result;
}

void Magician::Attack(Character* target)
{
	cout << "화염구를 발사했다!\n";
	target->Hit(mAttack);
}
