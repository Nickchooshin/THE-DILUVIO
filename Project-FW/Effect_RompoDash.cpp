#include "Effect_RompoDash.h"

CEffect_RompoDash::CEffect_RompoDash()
{
}
CEffect_RompoDash::~CEffect_RompoDash()
{
}

void CEffect_RompoDash::Init()
{
	LoadDat("Resource/Data/Effect/Rompo_dash_effect.dat") ;
}

void CEffect_RompoDash::Effect(CObjects *pObject)
{
	pObject->SendEventMessage("ROMPO", this) ;
}