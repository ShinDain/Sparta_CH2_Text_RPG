#include "Character.h"
#include "Player.h"

Character::Character()
{
}

Character::~Character()
{
}

bool Character::Initialize()
{
	bool result = true;
	mIsDead = false;

	return result;
}

void Character::PrintStats()
{
}

void Character::RecoveryHP(int amount, string instigatorName)
{
	mHP += amount;


	PrintFormatString("item_use_recovery_HP", { {"{Name}", instigatorName},{"{Value}", to_string(amount)}});
}

void Character::RecoveryMP(int amount, string instigatorName)
{
	mMP += amount;

	PrintFormatString("item_use_recovery_MP", { {"{Name}", instigatorName},{"{Value}", to_string(amount)} });
}

void Character::Hit(int damage)
{
	int resultDamage = max((damage - mDefence), 1);
	int preHP = mHP;
	int postHP = mHP - resultDamage;
	mHP = max(postHP, 0);

	PrintFormatString("combat_attack_result_1", { {"{Name}", mName},{"{Result}", to_string(resultDamage)}});
	PrintFormatString("combat_attack_result_2", { {"{Name}", mName},{"{PreValue}", to_string(preHP)}, {"{PostValue}", to_string(postHP)} });

	if (postHP <= 0)
	{
		PrintString("state_death");
		mIsDead = true;
	}
	else
	{
		cout << endl;
	}
}
