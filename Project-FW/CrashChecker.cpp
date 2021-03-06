#include "CrashChecker.h"
#include "Hero.h"
#include "Tiles.h"

CCrashChecker::CCrashChecker()
{
	rtIntersect.left = 0 ;
	rtIntersect.top = 0 ;
	rtIntersect.right = 0 ;
	rtIntersect.bottom = 0 ;
}
CCrashChecker::~CCrashChecker()
{
}

bool CCrashChecker::Crash(Rect A, Rect B)
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

void CCrashChecker::XCollision(CHero *pHero, CTiles *pTile)
{
	int way = -1 ;
	Vector vec = pHero->GetForce() ;
	Rect rtHero = pHero->GetBoundingBox() ;
	Rect rtTile = pTile->GetBoundingBox() ;
	int xSize = rtTile.right - rtTile.left  ;

	if(!Crash(rtHero, rtTile))
		return ;
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

	if(!Crash(rtHero, rtTemp))
		return ;

	int x = (int)pHero->GetPositionX() ;
	int y = (int)pHero->GetPositionY() ;

	if(way==0)
		x += (rtSize.right - rtSize.left) ;
	else
		x -= (rtSize.right - rtSize.left) ;

	pHero->SetPosition((float)x, (float)y) ;
}

void CCrashChecker::YCollision(CHero *pHero, CTiles *pTile)
{
	int way = -1 ;
	Vector vec = pHero->GetForce() ;
	Rect rtHero = pHero->GetBoundingBox() ;
	Rect rtTile = pTile->GetBoundingBox() ;
	int ySize = rtTile.top - rtTile.bottom  ;

	if(!Crash(rtHero, rtTile))
		return ;
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

	if(!Crash(rtHero, rtTemp))
		return ;
	Crash(rtHero, rtTile) ;

	int x = (int)pHero->GetPositionX() ;
	int y = (int)pHero->GetPositionY() ;

	if(way==0)
	{
		y += (rtSize.top - rtSize.bottom) ;
		pHero->SetJump(false) ;
		pHero->GravityAccReset() ;
	}
	else
	{
		y -= (rtSize.top - rtSize.bottom) ;
		pHero->SetJump(true) ;
		pHero->GravityAccReset() ;
	}

	pHero->SetPosition((float)x, (float)y) ;
}

Rect CCrashChecker::GetIntersect()
{
	return rtIntersect ;
}