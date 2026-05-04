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

	mClass.job = Job::Thief;
	mClass.name = "도적";
	mMP += 20;
	mAttack += 10;
	cout << "도적으로 전직하였습니다! (MP + 20, 공격력 + 10)\n";

	return result;
}

void Thief::Attack(Character* target)
{
	cout << "단검으로 찔렀다!\n";
	target->Hit(mAttack);
}
