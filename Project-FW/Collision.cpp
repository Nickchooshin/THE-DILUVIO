#include "Collision.h"
#include <math.h>
#include "DynamicObjects.h"
#include "Tiles.h"
#include "Effect.h"

#include <stdio.h>

CCollision::CCollision()
{
	rtIntersect.left = 0 ;
	rtIntersect.top = 0 ;
	rtIntersect.right = 0 ;
	rtIntersect.bottom = 0 ;
}
CCollision::~CCollision()
{
}

bool CCollision::AABB(Rect A, Rect B)
{
	bool bState=false ;

	if(A.left < B.right &&
	   A.right > B.left &&
	   A.top > B.bottom &&
	   A.bottom < B.top)
	{
		bState = true ;
	}

	if(A.top<B.top)
		rtIntersect.top = A.top ;
	else
		rtIntersect.top = B.top ;

	if(A.bottom>B.bottom)
		rtIntersect.bottom = A.bottom ;
	else
		rtIntersect.bottom = B.bottom ;

	if(A.left>B.left)
		rtIntersect.left = A.left ;
	else
		rtIntersect.left = B.left ;

	if(A.right<B.right)
		rtIntersect.right = A.right ;
	else
		rtIntersect.right = B.right ;
	
	return bState ;
}

bool CCollision::XCollision(CDynamicObjects *pDynamicObject, CObjects *pObject)
{
	int way = -1 ;
	Vector vec = pDynamicObject->GetForce() ;
	Rect rtDynamic = pDynamicObject->GetBoundingBox() ;
	Rect rtObject = pObject->GetBoundingBox() ;
	int xSize = rtObject.right - rtObject.left  ;

	if(!AABB(rtDynamic, rtObject))
		return false ;
	Rect rtSize = GetIntersect() ;

	if(vec.x<=0)
		way = 0 ;
	else
		way = 1 ;

	Rect rtTemp = rtObject ;
	if(way==0)
	{
		rtTemp.left += xSize ;
		rtTemp.right += xSize ;
	}
	else
	{
		rtTemp.left -= xSize ;
		rtTemp.right -= xSize ;
	}

	if(!AABB(rtDynamic, rtTemp))
		return false ;

	float x = pDynamicObject->GetPositionX() ;
	float y = pDynamicObject->GetPositionY() ;

	if(way==0)
	{
		x += (float)(rtSize.right - rtSize.left) ;
	}
	else
	{
		x -= (float)(rtSize.right - rtSize.left) ;
	}
	x = (int)x ;

	pDynamicObject->SetPosition(x, y) ;

	return true ;
}

bool CCollision::YCollision(CDynamicObjects *pDynamicObject, CObjects *pObject)
{
	int way = -1 ;
	Vector vec = pDynamicObject->GetForce() ;
	Rect rtDynamic = pDynamicObject->GetBoundingBox() ;
	Rect rtObject = pObject->GetBoundingBox() ;
	int ySize = rtObject.top - rtObject.bottom  ;

	if(!AABB(rtDynamic, rtObject))
		return false ;
	Rect rtSize = GetIntersect() ;

	if(vec.y<=0)
		way = 0 ;
	else
		way = 1 ;

	Rect rtTemp = rtObject ;
	if(way==0)
	{
		rtTemp.top += ySize ;
		rtTemp.bottom += ySize ;
	}
	else
	{
		rtTemp.top -= ySize ;
		rtTemp.bottom -= ySize ;
	}

	if(!AABB(rtDynamic, rtTemp))
		return false ;
	AABB(rtDynamic, rtObject) ;

	float x = pDynamicObject->GetPositionX() ;
	float y = pDynamicObject->GetPositionY() ;

	if(way==0)
	{
		y += (rtSize.top - rtSize.bottom) ;
		pDynamicObject->SetJump(false) ;
		pDynamicObject->GravityAccReset() ;
		pDynamicObject->SetGravity(false) ;
	}
	else
	{
		y -= (rtSize.top - rtSize.bottom) ;
		pDynamicObject->SetJump(true) ;
		pDynamicObject->GravityAccReset() ;
	}
	y = (int)y ;

	pDynamicObject->SetPosition(x, y) ;

	return true ;
}

//

bool CCollision::XCollision(CDynamicObjects *pDynamicObject, CTiles *pTile)
{
	//
	if(!pTile->BeCollision())
	{
		Rect rtDynamic = pDynamicObject->GetBoundingBox() ;
		Rect rtTile = pTile->GetBoundingBox() ;

		if(AABB(rtDynamic, rtTile))
		{
			//
			Vector vec = pDynamicObject->GetForce() ;
			if(vec.x<=0)
				pTile->CollisionDirection(CTiles::COLLISION_RIGHT) ;
			else
				pTile->CollisionDirection(CTiles::COLLISION_LEFT) ;
			//

			pTile->Effect1(pDynamicObject) ;
			return true ;
		}

		return false ;
	}
	//

	int way = -1 ;
	Vector vec = pDynamicObject->GetForce() ;
	Rect rtDynamic = pDynamicObject->GetBoundingBox() ;
	Rect rtTile = pTile->GetBoundingBox() ;
	int xSize = rtTile.right - rtTile.left  ;

	if(!AABB(rtDynamic, rtTile))
		return false ;
	Rect rtSize = GetIntersect() ;

	if(vec.x<=0)
		way = 0 ;
	else
		way = 1 ;

	Rect rtTemp = rtTile ;
	if(way==0)
	{
		rtTemp.left += xSize ;
		rtTemp.right += xSize ;
	}
	else
	{
		rtTemp.left -= xSize ;
		rtTemp.right -= xSize ;
	}

	if(!AABB(rtDynamic, rtTemp))
		return false ;

	float x = pDynamicObject->GetPositionX() ;
	float y = pDynamicObject->GetPositionY() ;

	if(way==0)
	{
		x += (rtSize.right - rtSize.left) ;
		pTile->CollisionDirection(CTiles::COLLISION_RIGHT) ;
	}
	else
	{
		x -= (rtSize.right - rtSize.left) ;
		pTile->CollisionDirection(CTiles::COLLISION_LEFT) ;
	}
	x = (int)x ;

	pDynamicObject->SetPosition(x, y) ;

	return true ;
}

bool CCollision::YCollision(CDynamicObjects *pDynamicObject, CTiles *pTile)
{
	//
	if(!pTile->BeCollision())
	{
		Rect rtDynamic = pDynamicObject->GetBoundingBox() ;
		Rect rtTile = pTile->GetBoundingBox() ;

		if(AABB(rtDynamic, rtTile))
		{
			//
			Vector vec = pDynamicObject->GetForce() ;
			if(vec.y<=0)
				pTile->CollisionDirection(CTiles::COLLISION_UP) ;
			else
				pTile->CollisionDirection(CTiles::COLLISION_DOWN) ;
			//

			pTile->Effect1(pDynamicObject) ;
			return true ;
		}

		return false ;
	}
	//

	int way = -1 ;
	Vector vec = pDynamicObject->GetForce() ;
	Rect rtDynamic = pDynamicObject->GetBoundingBox() ;
	Rect rtTile = pTile->GetBoundingBox() ;
	int ySize = rtTile.top - rtTile.bottom  ;

	if(!AABB(rtDynamic, rtTile))
		return false ;
	Rect rtSize = GetIntersect() ;

	if(vec.y<=0)
		way = 0 ;
	else
		way = 1 ;

	Rect rtTemp = rtTile ;
	if(way==0)
	{
		rtTemp.top += ySize ;
		rtTemp.bottom += ySize ;
	}
	else
	{
		rtTemp.top -= ySize ;
		rtTemp.bottom -= ySize ;
	}

	if(!AABB(rtDynamic, rtTemp))
		return false ;
	AABB(rtDynamic, rtTile) ;

	float x = pDynamicObject->GetPositionX() ;
	float y = pDynamicObject->GetPositionY() ;

	if(way==0)
	{
		y += (rtSize.top - rtSize.bottom) ;
		pDynamicObject->SetJump(false) ;
		pDynamicObject->GravityAccReset() ;
		pDynamicObject->SetGravity(false) ;
		pTile->CollisionDirection(CTiles::COLLISION_UP) ;
	}
	else
	{
		y -= (rtSize.top - rtSize.bottom) ;
		pDynamicObject->SetJump(true) ;
		pDynamicObject->GravityAccReset() ;
		pTile->CollisionDirection(CTiles::COLLISION_DOWN) ;
	}
	y = (int)y ;

	pDynamicObject->SetPosition(x, y) ;

	return true ;
}

Rect CCollision::GetIntersect()
{
	return rtIntersect ;
}

bool CCollision::DotCirleCollision(Position dot, Circle circle)
{
	float distance ;
	float x = (float)(circle.pos.x - dot.x) ;
	float y = (float)(circle.pos.y - dot.y) ;

	distance = sqrt((x*x) + (y*y)) ;

	if(distance<=circle.radius)
		return true ;

	return false ;
}

bool CCollision::DotCirleCollision(CObjects *pObject, CEffect *pEffect)
{
	float X, Y ;
	Rect ObjectRect ;
	Circle EffectCircle ;
	Position NearbyDot ;

	X = pObject->GetPositionX() ;
	Y = pObject->GetPositionY() ;

	ObjectRect = pObject->GetBoundingBox() ;
	EffectCircle = pEffect->GetBoundingCircle() ;

	if(X>EffectCircle.pos.x)
		NearbyDot.x = ObjectRect.left ;
	//else if(X<EffectCircle.pos.x)
	else
		NearbyDot.x = ObjectRect.right ;

	if(Y>EffectCircle.pos.y)
		NearbyDot.y = ObjectRect.bottom ;
	//else if(Y<EffectCircle.pos.y)
	else
		NearbyDot.y = ObjectRect.top ;

	if(DotCirleCollision(NearbyDot, EffectCircle))
		return true ;

	return false ;
}