#pragma once

#include "Effect.h"

class CEffect_RompoDash : public CEffect
{
private :
	char m_cDirection ;
	CObjects *m_pDashObject ;

public :
	CEffect_RompoDash() ;
	~CEffect_RompoDash() ;

	void Init() ;
	void Init(char direction) ;

	void Dash() ;
	void Crash() ;

	void Update() ;
	void Effect(CObjects *pObject) ;
private :
	void Move() ;
	void Animation() ;
} ;