#include "Item.h"

Item::Item(const ItemData* data)
	: mData(data)
{
}

Item::~Item()
{
}

void Item::PrintInfo()
{
	cout << GetName() << " (" << GetPrice() << "G)\n";
}
