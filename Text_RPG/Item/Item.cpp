#include "Item.h"

Item::Item(string itemName, int price)
	:mName(itemName), mPrice(price)
{
}

Item::~Item()
{
}

void Item::PrintInfo()
{
	cout << mName << " (" << mPrice << "G)\n";
}
