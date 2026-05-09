#include "Monster.h"

Monster::Monster(const MonsterData* data)
	: mData(data)
{
	mName = mData->Name;
	mLevel = mData->Level;
	mHP = mData->HP;
	mMP = mData->MP;
	mMaxHP = mData->HP;
	mMaxMP = mData->MP;
	mAttack = mData->Attack;
	mDefence = mData->Defence;
	mDropItemName = mData->DropItemName;
}

Monster::~Monster()
{
}

bool Monster::Initialize()
{
	return Character::Initialize();
}

void Monster::PrintStats()
{
	PrintString("double_line");
	PrintFormatString("print_monster_stat_1", { {"{Name}", mName} });
	PrintString("double_line");
	PrintFormatString("print_monster_stat_2", { {"{Name}", mName}, {"{Level}", to_string(mLevel)}});
	PrintFormatString("print_monster_stat_3", { {"{HP}", to_string(mHP)}, {"{MP}", to_string(mMP)},{"{Attack}", to_string(mAttack)},{"{Defence}", to_string(mDefence)} });
	PrintString("double_line");
}

void Monster::Attack(Character* target)
{
	PrintFormatString("combat_monster_attack", { {"{Name}", mName} });
	target->Hit(mAttack);
}

int Monster::GetRewardExp(int opponentLevel)
{
	int reward = DEFAULT_REWARD_EXP;

	if (opponentLevel < mLevel)
	{
		int gap = mLevel - opponentLevel;
		reward += gap * (DEFAULT_REWARD_EXP / 10);
	}
    
	return reward;
}

