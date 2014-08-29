#pragma once

#include "Effect.h"

class CEffect_RanchoEat : public CEffect
{
public :
	CEffect_RanchoEat() ;
	~CEffect_RanchoEat() ;

	void Init() ;
	
	void Effect(CObjects* pObject) ;

	int GetAniFrame() ;
private :
	void Animation() ;
} ;