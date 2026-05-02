#pragma once
#include <string>

using namespace std;

class Character;

class Item
{
public:
	Item();
	virtual ~Item();

	virtual void Active(Character* instigator) {};

	string GetName() { return mName; }
protected:
	string mName;
};

