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
		rtSize = GetIntersect() ;

		// left
		rtTemp = rtTile ;
		rtTemp.left -= x ;
		rtTemp.right -= x ;

		Crash(rtHero, rtTemp) ;
		rtTemp = GetIntersect() ;
		temp = (rtTemp.right - rtTemp.left) * (rtTemp.top - rtTemp.bottom) ;
		if(temp>size)
		{
			size = temp ;
			way = 0 ;
		}

		// right
		rtTemp = rtTile ;
		rtTemp.left += x ;
		rtTemp.right += x ;

		Crash(rtHero, rtTemp) ;
		rtTemp = GetIntersect() ;
		temp = (rtTemp.right - rtTemp.left) * (rtTemp.top - rtTemp.bottom) ;
		if(temp>size)
		{
			size = temp ;
			way = 1 ;
		}

		// top
		rtTemp = rtTile ;
		rtTemp.top += y ;
		rtTemp.bottom += y ;

		Crash(rtHero, rtTemp) ;
		rtTemp = GetIntersect() ;
		temp = (rtTemp.right - rtTemp.left) * (rtTemp.top - rtTemp.bottom) ;
		if(temp>size)
		{
			size = temp ;
			way = 2 ;
		}

		// bottom
		rtTemp = rtTile ;
		rtTemp.top -= y ;
		rtTemp.bottom -= y ;

		Crash(rtHero, rtTemp) ;
		rtTemp = GetIntersect() ;
		temp = (rtTemp.right - rtTemp.left) * (rtTemp.top - rtTemp.bottom) ;
		if(temp>size)
		{
			size = temp ;
			way = 3 ;
		}



		//float x = pHero->GetPositionX() ;
		//float y = pHero->GetPositionY() ;
		int x = pHero->GetPositionX() ;
		int y = pHero->GetPositionY() ;
		// float 사용 시 소수점 차이의 오차로 인하여, 계속해서 1픽셀 간격으로 불균형함을 이룸.
		// 반올림 단위로 sprite 위치를 지정해서 그런듯

		switch(way)
		{
		case 0 : // l
			x -= (rtSize.right - rtSize.left) ;
			break ;

		case 1 : // r
			x += (rtSize.right - rtSize.left) ;
			break ;

		case 2 : // t
			y += (rtSize.top - rtSize.bottom) ;
			pHero->GravityReset() ;
			break ;

		case 3 : // b
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