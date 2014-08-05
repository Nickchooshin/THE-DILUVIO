#pragma once

#include "Effect.h"

class CEffect_SparkArea : public CEffect
{
public :
	CEffect_SparkArea() ;
	~CEffect_SparkArea() ;

	void Init() ;

	void Effect(CObjects* pObject) ;
} ;