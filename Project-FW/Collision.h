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

	void XCollision(CDynamicObjects *pDynamicObject, CObjects *pObject) ;
	void YCollision(CDynamicObjects *pDynamicObject, CObjects *pObject) ;

	void XCollision(CDynamicObjects *pDynamicObject, CTiles *pTile) ;
	void YCollision(CDynamicObjects *pDynamicObject, CTiles *pTile) ;

	Rect GetIntersect() ;
} ;