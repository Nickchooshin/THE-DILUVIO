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
	float xSize = rtObject.right - rtObject.left  ;

	if(!AABB(rtDynamic, rtObject))
		return false ;
	Rect rtSize = GetIntersect() ;

	/*if(vec.x<=0)
		way = 0 ;
	else
		way = 1 ;*/
	if(vec.x<0)
		way = 0 ;
	else if(vec.x>0)
		way = 1 ;
	else
	{
		float DynamicObjectX = pDynamicObject->GetPositionX() ;
		float ObjectX = pObject->GetPositionX() ;

		if(DynamicObjectX>ObjectX)
			way = 0 ;
		else if(DynamicObjectX<ObjectX)
			way = 1 ;
	}

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
	x = x ;

	pDynamicObject->SetPosition(x, y) ;

	return true ;
}

bool CCollision::YCollision(CDynamicObjects *pDynamicObject, CObjects *pObject)
{
	int way = -1 ;
	Vector vec = pDynamicObject->GetForce() ;
	Rect rtDynamic = pDynamicObject->GetBoundingBox() ;
	Rect rtObject = pObject->GetBoundingBox() ;
	float ySize = rtObject.top - rtObject.bottom  ;

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
	y = y ;

	pDynamicObject->SetPosition(x, y) ;

	return true ;
}

//

bool CCollision::XCollision(CDynamicObjects *pDynamicObject, CTiles *pTile)
{
	//
	if(!pTile->BeCollision() && pTile->BeNonCollision(pDynamicObject))
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
	float xSize = rtTile.right - rtTile.left  ;

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
	x = x ;

	pDynamicObject->SetPosition(x, y) ;

	return true ;
}

bool CCollision::YCollision(CDynamicObjects *pDynamicObject, CTiles *pTile)
{
	//
	if(!pTile->BeCollision() && pTile->BeNonCollision(pDynamicObject))
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
	float ySize = rtTile.top - rtTile.bottom  ;

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
	y = y ;

	pDynamicObject->SetPosition(x, y) ;

	return true ;
}

Rect CCollision::GetIntersect()
{
	return rtIntersect ;
}

bool CCollision::CircleCollision(Circle A, Circle B)
{
	float distance ;
	float x = (float)(B.pos.x - A.pos.x) ;
	float y = (float)(B.pos.y - A.pos.y) ;

	distance = sqrt((x*x) + (y*y)) ;

	if(distance<=(A.radius + B.radius))
		return true ;

	return false ;
}

bool CCollision::RectCircleCollision(CObjects *pObject, CEffect *pEffect)
{
	Rect ObjectRect = pObject->GetBoundingBox() ;
	Circle EffectCircle = pEffect->GetBoundingCircle() ;

	float x = pObject->GetPositionX() ;
	float y = pObject->GetPositionY() ;

	// ObjectRect의 영역을 감싸는 넓이의 원을 구해야 하므로
	// ObjectRect의 원점에서 꼭지점 까지의 거리를 원의 반지름으로 정한다
	float xx = (ObjectRect.right - x) ;
	float yy = (ObjectRect.top - y) ;
	float distance = sqrt((xx*xx) + (yy*yy)) ;

	Circle ObjectCircle ;
	ObjectCircle.pos.x = x ;
	ObjectCircle.pos.y = y ;
	ObjectCircle.radius = distance ;

	if(CircleCollision(ObjectCircle, EffectCircle))
	{
		// EffectRect는 EffectCircle의 넓이에 딱 맞는
		// 사각형을 구하면 된다
		Rect EffectRect ;
		EffectRect.left = EffectCircle.pos.x - EffectCircle.radius ;
		EffectRect.right = EffectCircle.pos.x + EffectCircle.radius ;
		EffectRect.top = EffectCircle.pos.y + EffectCircle.radius ;
		EffectRect.bottom = EffectCircle.pos.y - EffectCircle.radius ;

		if(AABB(EffectRect, ObjectRect))
			return true ;
	}

	return false ;
}