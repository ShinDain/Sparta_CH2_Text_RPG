#pragma once
#include "../CommonInclude.h"
#include "../System/Data/StringTable.h"

class Character
{
protected:
	Character() {};
public:
	virtual ~Character() {};

	virtual bool Initialize();
	virtual void PrintStats() {};

	void RecoveryHP(int amount, string instigatorName);
	void RecoveryMP(int amount, string instigatorName);

	virtual void GainEXP(int value);
	virtual void LevelUp(int value);

	virtual void Attack(Character* target) = 0;
	virtual void Hit(int damage);
protected:
	bool SetLevelData(int value);
protected:
	string mName;

	uint32_t mLevel;
	uint32_t mExp;
	uint32_t mMaxExp;

	uint32_t mHP;
	uint32_t mMP;
	uint32_t mMaxHP;
	uint32_t mMaxMP;
	uint32_t mAttack;
	uint32_t mDefence;

	bool mIsDead;

public:
	string GetName() const { return mName; }
	int GetHP() const { return mHP; }
	int GetMP() const { return mMP; }
	int GetAttack() const { return mAttack; }
	int GetDefence() const { return mDefence; }
	int GetLevel() const { return mLevel; }
	int GetExp() const { return mExp; }
	int GetMaxExp() const { return mMaxExp; }

	void SetAttack(int InValue) { mAttack = InValue; }
	void SetDefence(int InValue) { mDefence = InValue; }

	bool IsDead() { return mIsDead; }
	bool IsAlive() { return !mIsDead; }
};

