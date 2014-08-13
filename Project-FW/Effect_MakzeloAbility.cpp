#include "Effect_MakzeloAbility.h"

CEffect_MakzeloAbility::CEffect_MakzeloAbility()
{
}
CEffect_MakzeloAbility::~CEffect_MakzeloAbility()
{
}

void CEffect_MakzeloAbility::Init()
{
	LoadDat("Resource/Data/Effect/Makzelo_ability.dat") ;
}

void CEffect_MakzeloAbility::Effect(CObjects *pObject)
{
	pObject->SendEventMessage("RESPIRATION") ;
}