#pragma once

#include "Effect.h"

class CEffect_Soul : public CEffect
{
public :
	CEffect_Soul() ;
	~CEffect_Soul() ;

	void Init() ;

	void SetDirection() ;

	void Update() ;

	void Render() ;
private :
	void Animation() ;
} ;