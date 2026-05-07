#pragma once
#include "../CommonInclude.h"
#include "../System/Data/ItemTable.h"

class Character;

struct Recipe
{
	vector<pair<string, int>> ingredients;
	string result;

	void Print()
	{
		cout << "-> " << result << " (";
		string sep = "";
		for (const auto& pair : ingredients)
		{
			string name = pair.first;
			int amount = pair.second;

			cout << sep;
			cout << name << " x" << amount;
			sep = ", ";
		}
		cout << ")\n";
	}
};

class Item
{
public:
	Item() = delete;
	Item(const ItemData* data);
	virtual ~Item();

	virtual void Active(Character* instigator) {};
	void PrintInfo();

protected:
	const ItemData* mData;

public:
	string GetName() { return mData->Name; }
	int GetPrice() { return mData->Price; }
};

