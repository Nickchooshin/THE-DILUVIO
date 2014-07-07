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

int CCrashChecker::Crash_CharAndTile(CHero *pHero, CTiles *pTile)
{
	RECT rtHero = pHero->GetBoundingBox() ;
	RECT rtTile = pTile->GetBoundingBox() ;
	RECT rtTemp, rtSize ;

	int x = rtTile.right - rtTile.left  ;
	int y = rtTile.top - rtTile.bottom ;

	int size=0, way=-1 ;
	int temp ;

	if(Crash(rtHero, rtTile))
	{
		Vector vec = pHero->GetForce() ;
		float xF = abs((int)vec.x) ;
		float yF = abs((int)vec.y) ;

		if(xF>=yF)
			way = vec.x<=0 ? 0 : 1 ;
		else
			way = vec.y<=0 ? 2 : 3 ;

		RECT rtTemp = rtTile ;
		switch(way)
		{
		case 0 : // RIGHT
			rtTemp.left += x ;
			rtTemp.right += x ;
			break ;

		case 1 : // LEFT
			rtTemp.left -= x ;
			rtTemp.right -= x ;
			break ;

		case 2 : // UP
			rtTemp.top += y ;
			rtTemp.bottom += y ;
			break ;

		case 3 : // DOWN
			rtTemp.top -= y ;
			rtTemp.bottom -= y ;
			break ;
		}

		if(!Crash(rtHero, rtTemp))
			return -1 ;
		Crash(rtHero, rtTile) ;
		rtSize = GetIntersect() ;

		int x = pHero->GetPositionX() ;
		int y = pHero->GetPositionY() ;
		switch(way)
		{
		case 0 :
			x += (rtSize.right - rtSize.left) ;
			pHero->GravityReset() ;
			break ;

		case 1 :
			x -= (rtSize.right - rtSize.left) ;
			pHero->GravityReset() ;
			break ;

		case 2 :
			y += (rtSize.top - rtSize.bottom) ;
			pHero->GravityReset() ;
			break ;

		case 3 :
			y -= (rtSize.top - rtSize.bottom) ;
			pHero->GravityReset() ;
			break ;
		}

		pHero->SetPosition(x, y) ;
	}

	return way ;
}

bool CCrashChecker::Crash(RECT A, RECT B)
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

RECT CCrashChecker::GetIntersect()
{
	return rtIntersect ;
}