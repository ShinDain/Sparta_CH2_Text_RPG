#pragma once
#include <map>
#include <string>
#include "../Item/Item.h"

using namespace std;

class Character;

struct InventoryEntry
{
	Item* Instance;
	int Amount;

	InventoryEntry()
		:Instance(nullptr), Amount(0)
	{}

	void Print()
	{
		cout << Instance->GetName() << " (" << Instance->GetPrice() << "G) " << Amount << "개\n";
	}
};

class InventoryComponent
{
public:
	InventoryComponent() = delete;
	InventoryComponent(Character* owner);
	virtual ~InventoryComponent();

	void Initialize();

	InventoryEntry* FindItem(string itemName);
	bool UseItem(string itemName);
	void AddItem(ItemData data, int amount);

	InventoryEntry* InitItemEntry(ItemData data);

	void PrintInventory();

	//template<typename T> 
	//ItemData* InitItemData();
private:
	map<string, InventoryEntry*> mItems;

	Character* mOwner;
public:
	int GetItemAmount(string itemName);
};

//template<typename T>
//inline ItemData* InventoryComponent::InitItemData()
//{
//	ItemData* itemData = new ItemData();
//	itemData->Instance = new T();
//	if (itemData->Instance)
//	{
//		itemData->Name = itemData->Instance->GetName();
//		itemData->Amount = 0;
//	}
//
//	mItems.emplace(itemData->Name, itemData);
//
//	return itemData;
//}
