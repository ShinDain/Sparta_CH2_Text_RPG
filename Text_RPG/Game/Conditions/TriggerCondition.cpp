#include "TriggerCondition.h"

TriggerCondition::TriggerCondition()
{
	mTrigger = false;
}

void TriggerCondition::Init()
{
	mTrigger = false;
}

void TriggerCondition::OnNotify()
{
	mTrigger = !mTrigger;
}

bool TriggerCondition::Check()
{
    return mTrigger;
}

