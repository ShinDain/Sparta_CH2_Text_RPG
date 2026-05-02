#pragma once
#include "Item.h"

class MPPotion : public Item
{
public:
	MPPotion();

	virtual void Active(Character* instigator) override;

private:
	int mAmount;
};
