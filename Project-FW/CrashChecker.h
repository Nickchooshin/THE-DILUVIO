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

	bool Crash(RECT A, RECT B) ;

	void XCollision(CHero *pHerol, CTiles *pTile) ;
	void YCollision(CHero *pHerol, CTiles *pTile) ;

	RECT GetIntersect() ;
} ;