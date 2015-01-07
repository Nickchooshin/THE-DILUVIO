#pragma once

#include "Effect.h"

class CEffect_Bubble : public CEffect
{
public :
	CEffect_Bubble() ;
	~CEffect_Bubble() ;

	void Init() ;

	void SetDirection() ;

	void Update() ;

	void Render() ;
private :
	void Animation() ;
} ;