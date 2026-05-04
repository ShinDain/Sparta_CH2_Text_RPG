#include "Component.h"

Component::Component(Character* owner, string name)
	:mOwner(owner), mName(name)
{
}

Component::~Component()
{
	mOwner = nullptr;
}
