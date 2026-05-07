#pragma once
#include "../CommonInclude.h"

const int SIZE = 4;

class Character
{
public:
	Character();
	virtual ~Character();

	virtual bool Initialize();
	virtual void PrintStats();

	void RecoveryHP(int amount);
	void RecoveryMP(int amount);

	virtual void Attack(Character* target) = 0;
	virtual void Hit(int damage);

protected:
	string mName;

	int mLevel;
	int mMaxHP;
	int mHP;
	int mMP;
	int mAttack;
	int mDefence;

	bool mIsDead;

public:
	string GetName() const { return mName; }
	int GetHP() const { return mHP; }
	int GetMP() const { return mMP; }
	int GetAttack() const { return mAttack; }
	int GetDefence() const { return mDefence; }
	int GetLevel() const { return mLevel; }

	void SetAttack(int InValue) { mAttack = InValue; }
	void SetDefence(int InValue) { mDefence = InValue; }

	bool IsDead() { return mIsDead; }
	bool IsAlive() { return !mIsDead; }
};

