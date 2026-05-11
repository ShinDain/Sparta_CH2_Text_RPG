#pragma once
#include "Character.h"
#include "../Component/Component.h"

struct ItemData;

class Player : public Character
{
public:
	enum class PlayerJob
	{
		Novice,
		Warrior,
		Magician,
		Thief,
		Archer,
		End,
	};

	struct Class
	{
		PlayerJob Job;
		string Name;

		Class()
			: Job(PlayerJob::Novice), Name("초보자")
		{}
	};

public:
	Player() = delete;
	Player(string name, int hp, int mp, int Attack, int defence);
	virtual ~Player();

	virtual bool Initialize() override;
	virtual void PrintStats() override;

	void AcquireItem(const string& itemName, int amount);
	bool UseItem(string itemName);

	void PrintInventory();

	template<typename T>
	T* AddComponent(string compName);
	template<typename T>
	T* FindComponent(string compName);

protected:
	Class mClass;

	vector<Component*> mComponents;
public:
	virtual string GetClassName() { return mClass.Name; }
};

template<typename T>
inline T* Player::AddComponent(string compName)
{
	T* newComp = new T(this, compName);
	if (newComp)
	{
		mComponents.emplace_back(newComp);
		return newComp;
	}

	return nullptr;
}

template<typename T>
inline T* Player::FindComponent(string compName)
{
	for (const auto& comp : mComponents)
	{
		if (compName == comp->GetName())
			return dynamic_cast<T*>(comp);
	}

	return nullptr;
}
