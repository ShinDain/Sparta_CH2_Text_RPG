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

	mClass.job = Job::Archer;
	mClass.name = "궁수";
	mHP -= 10;
	mAttack += 20;
	cout << "궁수로 전직하였습니다! (HP - 10, 공격력 + 20)\n";

	Attack();

	return result;
}

void Archer::Attack()
{
	cout << "화살을 쏘았다!";
}
