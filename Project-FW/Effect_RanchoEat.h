#pragma once

#include "Effect.h"

class CEffect_RanchoEat : public CEffect
{
private :
	CObjects *m_pTarget ;

public :
	CEffect_RanchoEat() ;
	~CEffect_RanchoEat() ;

	void Init() ;

	void SetTarget(CObjects *pTarget) ;
	
	void Update() ;
	void Effect(CObjects* pObject) ;

	int GetAniFrame() ;
private :
	void Animation() ;
} ;