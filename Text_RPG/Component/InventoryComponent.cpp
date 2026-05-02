#include "InventoryComponent.h"
#include "../Item/Item.h"
#include "../Item/HPPotion.h"
#include "../Item/MPPotion.h"

InventoryComponent::InventoryComponent(Character* owner)
	:mOwner (owner)
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
	InitItemData<HPPotion>();
	InitItemData<MPPotion>();
}

ItemData* InventoryComponent::FindItem(string itemName)
{
	if (mItems.find(itemName) != mItems.end())
	{
		return mItems[itemName];
	}

	return nullptr;
}

bool InventoryComponent::UseItem(string itemName)
{
	ItemData* itemData = FindItem(itemName);

	if (itemData)
	{
		if (itemData->Amount > 0)
		{
			itemData->Instance->Active(mOwner);
			itemData->Amount--;

			return true;
		}
	}

	return false;
}

void InventoryComponent::AddItem(string itemName, int amount)
{
	ItemData* itemData = FindItem(itemName);

	if (itemData)
	{
		itemData->Amount += amount;
	}
}
