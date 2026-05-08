#include "InventoryComponent.h"
#include "../Item/Item.h"
#include "../System/Data/ItemTable.h"

InventoryComponent::InventoryComponent(Character* owner, string name)
	:Component(owner, name)
{
}

InventoryComponent::~InventoryComponent()
{
	mOwner = nullptr;
	for (auto& pair : mItems)
	{
		delete pair.second->Instance;
		pair.second->Instance = nullptr;

		delete pair.second;
		pair.second = nullptr;
	}
}

void InventoryComponent::Initialize()
{

}

InventoryEntry* InventoryComponent::FindItem(string itemName)
{
	if (mItems.find(itemName) != mItems.end())
	{
		return mItems[itemName];
	}

	return nullptr;
}

bool InventoryComponent::UseItem(string itemName)
{
	InventoryEntry* inventoryEntry = FindItem(itemName);

	if (inventoryEntry)
	{
		if (inventoryEntry->Amount > 0)
		{
			inventoryEntry->Instance->Active(mOwner);
			inventoryEntry->Amount--;

			return true;
		}
	}

	return false;
}

void InventoryComponent::AddItem(const ItemData* data, int amount)
{
	InventoryEntry* inventoryEntry = FindItem(data->Name);

	if (inventoryEntry)
	{
		inventoryEntry->Amount += amount;
	}
	else
	{
		InventoryEntry* newEntry = InitItemEntry(data);
		if (newEntry)
		{
			newEntry->Amount += amount;
		}
	}
}

InventoryEntry* InventoryComponent::InitItemEntry(const ItemData* data)
{
	string itemName = data->Name;
	int itemPrice = data->Price;

	InventoryEntry* itemEntry = new InventoryEntry();
	if (itemEntry)
	{
		itemEntry->Instance = new Item(data);
		if (itemEntry->Instance)
		{
			itemEntry->Amount = 0;
			mItems.emplace(itemName, itemEntry);
		}
	}
	return itemEntry;
}

void InventoryComponent::PrintInventory()
{
	int inventoryIdx = 0;
	for (const auto& pair : mItems)
	{
		// +1 하여 1부터 출력한다.
		InventoryEntry* Entry = pair.second;
		Entry->Print(inventoryIdx + 1);

		++inventoryIdx;
	}
}

int InventoryComponent::GetItemAmount(string itemName)
{
	InventoryEntry* Entry = FindItem(itemName);
	if (Entry)
	{
		return Entry->Amount;
	}

	return 0;
}
