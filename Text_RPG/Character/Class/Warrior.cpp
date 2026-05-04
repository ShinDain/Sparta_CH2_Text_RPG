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

	mClass.job = Job::Warrior;
	mClass.name = "전사";
	mHP += 20;
	mDefence += 10;
	cout << "전사로 전직하였습니다! (HP + 20, 방어력 + 10)\n";

	Attack();

	return result;
}

void Warrior::Attack()
{
	cout << "검으로 내리쳤다!";
}
