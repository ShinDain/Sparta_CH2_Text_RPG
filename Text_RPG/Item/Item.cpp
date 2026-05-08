#include "Item.h"
#include "../System/Data/StringTable.h"

Item::Item(const ItemData* data)
	: mData(data)
{
}

Item::~Item()
{
}

void Item::PrintInfo()
{
	int price = GetPrice();
	PrintFormatString("print_item_data", { {"{Name}", GetName()}, {"{Price}", to_string(price)} });
}
