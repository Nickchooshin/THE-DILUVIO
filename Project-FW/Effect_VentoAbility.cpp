#include "Effect_VentoAbility.h"

CEffect_VentoAbility::CEffect_VentoAbility()
{
}
CEffect_VentoAbility::~CEffect_VentoAbility()
{
}

void CEffect_VentoAbility::Init()
{
	LoadDat("Resource/Data/Effect/Vento_ability.dat") ;
}

void CEffect_VentoAbility::Effect(CObjects *pObject)
{
	pObject->SendEventMessage("CREEPER") ;
}