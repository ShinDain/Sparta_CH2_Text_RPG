#pragma once
#include "../State.h"

class TriggerCondition : public Condition
{
public:
	TriggerCondition();

	virtual void Init() override;
	virtual void OnNotify() override;
	virtual bool Check() override;
private:
	bool mTrigger;
};
