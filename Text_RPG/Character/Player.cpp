#include "Player.h"
#include "../Component/Component.h"

#include "../Component/InventoryComponent.h"
#include "../Component/AlchemyComponent.h"

Player::Player(string name, int hp, int mp, int Attack, int defence)
	:Character(name, hp, mp, Attack, defence)
{

}

Player::~Player()
{
	for (Component* component : mComponents)
	{
		delete component;
		component = nullptr;
	}
}

bool Player::Initialize()
{
	AddComponent<InventoryComponent>("Inventory");
	AddComponent<AlchemyComponent>("Alchemy");

	for (Component* component : mComponents)
	{
		if (component)
		{
			component->Initialize();
		}
	}

	return true;
}

void Player::PrintStats()
{
	cout << "\n------------------------------------\n";
	cout << "닉네임: " << mName << " | 직업: " << GetClassName() << " | Lv." << mLevel;
	cout << "\nHP: " << mHP << " | MP : " << mMP << " | 공격력: " << mAttack << " | 방어력 : " << mDefence << "\n";
	cout << "------------------------------------\n";
}

void Player::PrintInventory()
{
	InventoryComponent* inventoryComp = FindComponent<InventoryComponent>("Inventory");
	if (inventoryComp)
	{
		inventoryComp->PrintInventory();
	}
}

void Player::AcquireItem(ItemData data, int amount)
{
	InventoryComponent* inventoryComp = FindComponent<InventoryComponent>("Inventory");
	if (inventoryComp)
	{
		inventoryComp->AddItem(data, amount);
	}
}

bool Player::UseItem(string itemName)
{
	InventoryComponent* inventoryComp = FindComponent<InventoryComponent>("Inventory");
	if (inventoryComp)
	{
		return inventoryComp->UseItem(itemName);
	}
	return false;
}
