#pragma once

#include "Objects.h"

class CObjects ;
class CDynamicObjects ;
class CTiles ;

class CCollision
{
private :
	Rect rtIntersect ;

public :
	CCollision() ;
	~CCollision() ;

	bool AABB(Rect A, Rect B) ;	// AABB Collision

	bool XCollision(CDynamicObjects *pDynamicObject, CObjects *pObject) ;
	bool YCollision(CDynamicObjects *pDynamicObject, CObjects *pObject) ;

	bool XCollision(CDynamicObjects *pDynamicObject, CTiles *pTile) ;
	bool YCollision(CDynamicObjects *pDynamicObject, CTiles *pTile) ;

	Rect GetIntersect() ;
} ;