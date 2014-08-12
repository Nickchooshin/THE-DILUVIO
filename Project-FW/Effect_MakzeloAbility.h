#pragma once

#include "Effect.h"

class CEffect_MakzeloAbility : public CEffect
{
public :
	CEffect_MakzeloAbility() ;
	~CEffect_MakzeloAbility() ;

	void Init() ;

	void Effect(CObjects *pObject) ;
} ;