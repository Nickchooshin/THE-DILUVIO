#pragma once

#include "Objects.h"

class CHero ;
class CTiles ;

class CCrashChecker
{
private :
	Rect rtIntersect ;

public :
	CCrashChecker() ;
	~CCrashChecker() ;

	bool Crash(Rect A, Rect B) ;

	void XCollision(CHero *pHerol, CTiles *pTile) ;
	void YCollision(CHero *pHerol, CTiles *pTile) ;

	Rect GetIntersect() ;
} ;