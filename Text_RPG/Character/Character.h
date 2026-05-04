#pragma once
#include "../CommonInclude.h"

const int SIZE = 4;

class Character
{
public:
	Character() = delete;
	Character(string name, int hp, int mp, int Attack, int defence);
	virtual ~Character();

	virtual bool Initialize();
	virtual void PrintStats();

	void RecoveryHP(int amount);
	void RecoveryMP(int amount);
protected:
	string mName;

	int mLevel;
	int mHP;
	int mMP;
	int mAttack;
	int mDefence;

public:
	string GetName() const { return mName; }
	int GetHP() const { return mHP; }
	int GetMP() const { return mMP; }
	int GetAttack() const { return mAttack; }
	int GetDefence() const { return mDefence; }
	int GetLevel() const { return mLevel; }

	void SetAttack(int InValue) { mAttack = InValue; }
	void SetDefence(int InValue) { mDefence = InValue; }
};

