#pragma once

#include "Effect.h"

class CEffect_BusxoAbility : public CEffect
{
public :
	CEffect_BusxoAbility() ;
	~CEffect_BusxoAbility() ;

	void Init() ;

	void Effect(CObjects *pObject) ;
} ;