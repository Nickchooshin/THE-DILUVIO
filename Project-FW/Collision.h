#pragma once

#include "Objects.h"

class CHero ;
class CTiles ;
class CObjects ;
class CDynamicObjects ;

class CCollision
{
private :
	Rect rtIntersect ;

public :
	CCollision() ;
	~CCollision() ;

	bool AABB(Rect A, Rect B) ;	// AABB Collision

	void XCollision(CDynamicObjects *pDynamicObject, CObjects *pObject) ;
	void YCollision(CDynamicObjects *pDynamicObject, CObjects *pObject) ;

	Rect GetIntersect() ;
} ;