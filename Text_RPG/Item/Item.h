#pragma once
#include "../CommonInclude.h"

class Character;

struct ItemData
{
	string Name;
	int Price;

	ItemData()
		:Name("None"), Price(0) {}
	ItemData(string name, int price)
		:Name(name), Price(price) {}
};

class Item
{
public:
	Item() = delete;
	Item(string itemName, int price);
	virtual ~Item();

	virtual void Active(Character* instigator) {};
	void PrintInfo();

protected:
	string mName;
	int mPrice;

public:
	string GetName() { return mName; }
	int GetPrice() { return mPrice; }
};

