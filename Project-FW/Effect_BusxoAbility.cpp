#include "Effect_BusxoAbility.h"

CEffect_BusxoAbility::CEffect_BusxoAbility()
{
}
CEffect_BusxoAbility::~CEffect_BusxoAbility()
{
}

void CEffect_BusxoAbility::Init()
{
	LoadDat("Resource/Data/Effect/Busxo_ability.dat") ;
}

void CEffect_BusxoAbility::Effect(CObjects *pObject)
{
	pObject->SendEventMessage("BUSXO") ;
}