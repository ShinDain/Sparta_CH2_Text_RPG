#pragma once
#include <map>
#include <string>
#include "../Item/Item.h"

using namespace std;

class Character;

struct ItemData
{
	string Name;
	Item* Instance;
	int Amount;

	ItemData()
		:Name(), Instance(nullptr), Amount(0)
	{}
};

class InventoryComponent
{
public:
	InventoryComponent() = delete;
	InventoryComponent(Character* owner);
	virtual ~InventoryComponent();

	void Initialize();
	template<typename T> 
	ItemData* InitItemData();

	ItemData* FindItem(string itemName);
	bool UseItem(string itemName);
	void AddItem(string itemName, int amount);

private:
	map<string, ItemData*> mItems;

	Character* mOwner;
};

template<typename T>
inline ItemData* InventoryComponent::InitItemData()
{
	ItemData* itemData = new ItemData();
	itemData->Instance = new T();
	if (itemData->Instance)
	{
		itemData->Name = itemData->Instance->GetName();
		itemData->Amount = 0;
	}

	mItems.emplace(itemData->Name, itemData);

	return itemData;
}
