#pragma once
#include "../State.h"

class AlwaysTrueCondition : public Condition
{
public:
	virtual bool Check() override;
};
