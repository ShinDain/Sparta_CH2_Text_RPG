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
	mClass.Name = "궁수";
	mHP -= 45;
	mAttack += 20;
	cout << "궁수로 전직하였습니다! (HP - 45, 공격력 + 20)\n";

	return result;
}

void Archer::Attack(Character* target)
{
	cout << "화살을 쏘았다!\n";
	target->Hit(mAttack);
}
