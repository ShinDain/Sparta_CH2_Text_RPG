#include "Character.h"
#include <iostream>

Character::Character()
{
}

Character::Character(const string& InName)
	: mName(InName)
{
}

Character::~Character()
{
}

bool Character::Initialize()
{
	bool result = true;

	result = InitializeName();

	cout << "HP와 MP를 입력해주세요 : ";
	result = InitializeTwoStats(STAT_INDEX::HP, STAT_INDEX::MP);
	cout << "공격력과 방어력을 입력해주세요 : ";
	result = InitializeTwoStats(STAT_INDEX::ATTACK, STAT_INDEX::DEFENCE);

	return result;
}

void Character::PrintStats()
{
	cout << "\n====================================\n";
	cout << mName << " 의 현재 능력치\n";
	cout << "====================================\n";
	cout << "HP: " << mStats[(int)STAT_INDEX::HP] << "    MP : " << mStats[(int)STAT_INDEX::MP] << "\n";
	cout << "공격력: " << mStats[(int)STAT_INDEX::ATTACK] << "    방어력 : " << mStats[(int)STAT_INDEX::DEFENCE] << "\n";
	cout << "====================================\n";
}

bool Character::InitializeName()
{
	cout << "용사의 이름을 입력해주세요 : ";
	string InName;
	cin >> InName;

	mName = InName;

	cout << "\n";

	return true;
}

bool Character::InitializeTwoStats(STAT_INDEX StatIndex1, STAT_INDEX StatIndex2)
{
	int Input1, Input2 = 0;
	while (true)
	{
		cin >> Input1 >> Input2;

		if (IsValidStatValue(StatIndex1, Input1)
			&& IsValidStatValue(StatIndex2, Input2))
		{
			mStats[(int)StatIndex1] = Input1;
			mStats[(int)StatIndex2] = Input2;
			break;
		}
	}

	return true;
}

bool Character::IsValidStatValue(STAT_INDEX StatIndex, int InValue)
{
	bool result = true;

	switch (StatIndex)
	{
	case Character::STAT_INDEX::HP:
	case Character::STAT_INDEX::MP:
		if (InValue < 50)
		{
			cout << "HP 또는 MP가 너무 작습니다. 다시 입력해주세요. (50 이상)\n";
			cout << "HP와 MP를 입력해주세요 : ";
			result = false;
		}
		break;
	case Character::STAT_INDEX::ATTACK:
	case Character::STAT_INDEX::DEFENCE:
		if (InValue <= 0)
		{
			cout << "공격력 또는 방어력이 너무 작습니다. 다시 입력해주세요. (1 이상)\n";
			cout << "공격력과 방어력을 입력해주세요 : ";
			result = false;
		}
		break;
	default:
		break;
	}

	return result;
}
