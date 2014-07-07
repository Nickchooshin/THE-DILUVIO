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

	int xSize = rtTile.right - rtTile.left  ;
	int ySize = rtTile.top - rtTile.bottom ;

	int size=0, way=-1 ;
	int temp ;

	if(Crash(rtHero, rtTile))
	{
		Vector force = pHero->GetForce() ;
		RECT rtTemp ;
		int y = (int)pHero->GetPositionY() ;
		int x = (int)pHero->GetPositionX() ;

		rtTemp = rtTile ;
		if(force.y<=0.0f)
		{
			rtTemp.top += ySize ;
			rtTemp.bottom += ySize ;
		}
		else
		{
			rtTemp.top -= ySize ;
			rtTemp.bottom -= ySize ;
		}

		if(Crash(rtHero, rtTemp))
		{
			Crash(rtHero, rtTile) ;
			rtSize = GetIntersect() ;

			if(force.y<0.0f)
				y += (rtSize.top - rtSize.bottom) ;
			else if(force.y>0.0f)
				y -= (rtSize.top - rtSize.bottom) ;

			pHero->GravityReset() ;
		}



		rtTemp = rtTile ;
		if(force.x<=0.0f)
		{
			rtTemp.left += xSize ;
			rtTemp.right += xSize ;
		}
		else
		{
			rtTemp.left -= xSize ;
			rtTemp.right -= xSize ;
		}

		pHero->SetPosition(x, y) ;
		rtHero = pHero->GetBoundingBox() ;
		if(Crash(rtHero, rtTemp))
		{
			Crash(rtHero, rtTile) ;
			rtSize = GetIntersect() ;

			if(force.x<0.0f)
				x += (rtSize.right - rtSize.left) ;
			else if(force.x>0.0f)
				x -= (rtSize.right - rtSize.left) ;
		}

		pHero->SetPosition(x, y) ;

		//

		/*RECT rtTemp = rtTile ;
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
			break ;

		case 1 :
			x -= (rtSize.right - rtSize.left) ;
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

		pHero->SetPosition(x, y) ;*/
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