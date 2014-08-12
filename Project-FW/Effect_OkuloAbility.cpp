#include "Effect_OkuloAbility.h"

CEffect_OkuloAbility::CEffect_OkuloAbility()
{
}
CEffect_OkuloAbility::~CEffect_OkuloAbility()
{
}

void CEffect_OkuloAbility::Init()
{
	LoadDat("Resource/Data/Effect/Okulo_ability.dat") ;
}

void CEffect_OkuloAbility::Effect(CObjects *pObject)
{
	pObject->SendEventMessage("GLASS") ;
}