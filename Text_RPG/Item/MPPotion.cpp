#include "MPPotion.h"
#include "../Character/Character.h"

MPPotion::MPPotion()
	:mAmount(20)
{
	mName = "MPPotion";
}

void MPPotion::Active(Character* instigator)
{
	if (instigator)
	{
		instigator->RecoveryMP(mAmount);
	}
}
