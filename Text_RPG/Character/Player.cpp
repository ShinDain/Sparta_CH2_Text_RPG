#include "Player.h"


Player::Player(string name, int hp, int mp, int Attack, int defence)
	:Character(name, hp, mp, Attack, defence)
{
	mInventoryComp = nullptr;
}

Player::~Player()
{
	delete mInventoryComp;
	mInventoryComp = nullptr;
}

bool Player::Initialize()
{
	mInventoryComp = new InventoryComponent(this);
	if (mInventoryComp == nullptr)
		return false;
	mInventoryComp->Initialize();


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
	mInventoryComp->PrintInventory();
}

void Player::AcquireItem(ItemData data, int amount)
{
	mInventoryComp->AddItem(data, amount);
}

bool Player::UseItem(string itemName)
{
	return mInventoryComp->UseItem(itemName);
}
