#include "Monster.h"

Monster::Monster(const MonsterData* data)
	: mData(data)
{
	mName = mData->Name;
	mMaxHP = mData->HP;
	mHP = mData->HP;
	mMP = mData->MP;
	mAttack = mData->Attack;
	mDefence = mData->Defence;
	mDropItemName = mData->DropItemName;
}

Monster::~Monster()
{
}

bool Monster::Initialize()
{
	bool result = true;
	mIsDead = false;
	mHP = mMaxHP;

	return result;
}

void Monster::PrintStats()
{
	PrintString("double_line");
	PrintFormatString("print_stat_1", { {"{Name}", mName} });
	PrintString("double_line");
	PrintFormatString("print_stat_2", { {"{Name}", mName}, {"{Class}", "몬스터"}, {"{Level}", to_string(mLevel)}});
	PrintFormatString("print_stat_3", { {"{HP}", to_string(mHP)}, {"{MP}", to_string(mMP)},{"{Attack}", to_string(mAttack)},{"{Defence}", to_string(mDefence)} });
	PrintString("double_line");
}

void Monster::Attack(Character* target)
{
	PrintFormatString("combat_monster_attack", { {"{Name}", mName} });
	//cout << "\"" << mName << "\"의 몸통박치기!";
	target->Hit(mAttack);
}

