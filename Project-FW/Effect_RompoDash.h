#pragma once

#include "Effect.h"

class CEffect_RompoDash : public CEffect
{
public :
	CEffect_RompoDash() ;
	~CEffect_RompoDash() ;

	void Init() ;

	void Effect(CObjects *pObject) ;
} ;