#include "Character.h"
#include "../Data/Table/LevelDataTable.h"

bool Character::Initialize()
{
	bool result = true;
	SetLevelData(mLevel);

	mIsDead = false;
	mHP = mMaxHP;
	mMP = mMaxMP;

	return result;
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

void Character::GainEXP(int value)
{
	mExp += value;

	int curExp = GetExp();
	int maxExp = GetMaxExp();
	PrintFormatString("combat_end_result_exp", { {"{GainValue}", to_string(value)}, {"{CurValue}", to_string(curExp)}, {"{MaxValue}",to_string(maxExp)} });

	while (mExp >= mMaxExp)
	{
		LevelUp(mLevel + 1);
	}
}

void Character::LevelUp(int value)
{
	while (mLevel < value)
	{
		int preLevel = mLevel;
		int postLevel = mLevel + 1;

		if (SetLevelData(postLevel))
		{
			const LevelData* data = GetLevelData(postLevel);

			int incrementValue = data->IncrementStat;
			PrintString("event_level_up_1");
			PrintFormatString("event_level_up_2", { {"{PreValue}", to_string(preLevel)}, {"{PostValue}", to_string(postLevel)} });
			PrintFormatString("event_level_up_3", { {"{Value}", to_string(incrementValue)} });
		}
	}
}

void Character::Hit(int damage)
{
	int resultDamage = max((damage - (int)mDefence), 1);
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
}

bool Character::SetLevelData(int value)
{
	int targetLevel = value;
	if (targetLevel < 1)
	{
		targetLevel = 1;
	}

	const LevelData* data = GetLevelData(targetLevel);
	if (data != nullptr)
	{
		mExp -= mMaxExp;

		mLevel = data->Level;
		mMaxExp = data->MaxExp;
		mHP += data->IncrementStat;
		mMP += data->IncrementStat;
		mMaxHP += data->IncrementStat;
		mMaxMP += data->IncrementStat;
		mAttack += data->IncrementStat;
		mDefence += data->IncrementStat;
	}
	else
	{
		mExp -= mMaxExp;
		mLevel = targetLevel;

		return false;
	}

	return true;
}
