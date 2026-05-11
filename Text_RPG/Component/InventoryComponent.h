#pragma once
#include "Component.h"
#include "../Item/Item.h"

class Character;

struct InventoryEntry
{
	Item* Instance;
	int Amount;

	InventoryEntry()
		:Instance(nullptr), Amount(0)
	{}

	void Print(int index)
	{
		PrintFormatString("inventory_print_item", {
			  {"{Index}", to_string(index)}
			, {"{Name}", Instance->GetName()}
			, {"{Price}", to_string(Instance->GetPrice())}
			, {"{Amount}", to_string(Amount)}
			});
	}
};

class InventoryComponent : public Component
{
public:
	InventoryComponent() = delete;
	InventoryComponent(Character* owner, string name);
	virtual ~InventoryComponent();

	virtual void Initialize() override;

	InventoryEntry* FindItem(string itemName);
	bool UseItem(string itemName);
	void AddItem(const ItemData* data, int amount);

	InventoryEntry* InitItemEntry(const ItemData* data);

	void PrintInventory();
private:
	int mEntryCnt;
	map<string, InventoryEntry*> mItems;
public:
	int GetItemAmount(string itemName);
};
