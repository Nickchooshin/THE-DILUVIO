#pragma once

#include "Effect.h"

class CEffect_VentoAbility : public CEffect
{
public :
	CEffect_VentoAbility() ;
	~CEffect_VentoAbility() ;

	void Init() ;

	void Effect(CObjects *pObject) ;
} ;