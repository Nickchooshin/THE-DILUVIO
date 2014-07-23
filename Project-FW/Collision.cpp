#include "Collision.h"
#include "Hero.h"
#include "Tiles.h"

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

void CCollision::XCollision(CDynamicObjects *pDynamicObject, CObjects *pObject)
{
	int way = -1 ;
	Vector vec = pDynamicObject->GetForce() ;
	Rect rtDynamic = pDynamicObject->GetBoundingBox() ;
	Rect rtObject = pObject->GetBoundingBox() ;
	int xSize = rtObject.right - rtObject.left  ;

	if(!AABB(rtDynamic, rtObject))
		return ;
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
		return ;

	float x = pDynamicObject->GetPositionX() ;
	int y = (int)pDynamicObject->GetPositionY() ;

	if(way==0)
		x += (float)(rtSize.right - rtSize.left) ;
	else
		x -= (float)(rtSize.right - rtSize.left) ;

	pDynamicObject->SetPosition(x, (float)y) ;
}

void CCollision::YCollision(CDynamicObjects *pDynamicObject, CObjects *pObject)
{
	int way = -1 ;
	Vector vec = pDynamicObject->GetForce() ;
	Rect rtDynamic = pDynamicObject->GetBoundingBox() ;
	Rect rtObject = pObject->GetBoundingBox() ;
	int ySize = rtObject.top - rtObject.bottom  ;

	if(!AABB(rtDynamic, rtObject))
		return ;
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
		return ;
	AABB(rtDynamic, rtObject) ;

	float x = pDynamicObject->GetPositionX() ;
	int y = (int)pDynamicObject->GetPositionY() ;

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

	pDynamicObject->SetPosition(x, (float)y) ;
}

Rect CCollision::GetIntersect()
{
	return rtIntersect ;
}