#include "Player.h"
#include "../Component/Component.h"

#include "../Component/InventoryComponent.h"
#include "../Component/AlchemyComponent.h"
#include "../System/Data/ItemTable.h"

Player::Player(string name, int hp, int mp, int Attack, int defence)
{
	mName = name;
	mHP = hp;
	mMP = mp;
	mMaxHP = hp;
	mMaxMP = mp;
	mAttack = Attack;
	mDefence = defence;

	mExp = 0;
	mMaxExp = 0;
}

Player::~Player()
{
	for (Component* component : mComponents)
	{
		delete component;
	}
}

bool Player::Initialize()
{
	if (!Character::Initialize())
		return false;

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
	PrintString("double_line");
	PrintFormatString("print_player_stat_1", { {"{Name}", mName} });
	PrintString("double_line");
	PrintFormatString("print_player_stat_2", { {"{Name}", mName}
	, {"{Class}", GetClassName()}
	, {"{Level}", to_string(mLevel)}
	, {"{CurValue}", to_string(mExp) }
	, {"{MaxValue}", to_string(mMaxExp)} });
	PrintFormatString("print_player_stat_3", { {"{HP}", to_string(mHP)}, {"{MP}", to_string(mMP)},{"{Attack}", to_string(mAttack)},{"{Defence}", to_string(mDefence)}});
	PrintString("double_line");
}

void Player::PrintInventory()
{
	InventoryComponent* inventoryComp = FindComponent<InventoryComponent>("Inventory");
	if (inventoryComp)
	{
		inventoryComp->PrintInventory();
	}
}

void Player::AcquireItem(const ItemData* data, int amount)
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
