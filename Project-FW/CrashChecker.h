#pragma once

#include "Objects.h"

class CHero ;
class CTiles ;

class CCrashChecker
{
private :
	RECT rtIntersect ;

public :
	CCrashChecker() ;
	~CCrashChecker() ;

	int Crash_CharAndTile(CHero *pHero, CTiles *pTile) ;

	bool Crash(RECT A, RECT B) ;

	RECT GetIntersect() ;
} ;