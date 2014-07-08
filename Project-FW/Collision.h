#pragma once

#include "Objects.h"

class CHero ;
class CTiles ;

class CCollision
{
private :
	Rect rtIntersect ;

public :
	CCollision() ;
	~CCollision() ;

	bool AABB(Rect A, Rect B) ;	// AABB Collision

	void XCollision(CHero *pHerol, CTiles *pTile) ;
	void YCollision(CHero *pHerol, CTiles *pTile) ;

	Rect GetIntersect() ;
} ;