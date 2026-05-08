#pragma once
#include "../CommonInclude.h"
#include "../System/Data/StringTable.h"

class Character;

class Component
{
public:
	Component() = delete;
	Component(Character* owner, string name);
	virtual ~Component();

	virtual void Initialize() = 0;

protected:
	Character* mOwner;
	string mName;
public:
	string GetName() { return mName; }
};

