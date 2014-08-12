#pragma once

#include "Effect.h"

class CEffect_OkuloAbility : public CEffect
{
public :
	CEffect_OkuloAbility() ;
	~CEffect_OkuloAbility() ;

	void Init() ;

	void Effect(CObjects *pObject) ;
} ;