#pragma once

#include "Tiles.h"
#include <Windows.h>

class CTilesWater : public CTiles
{
private :
	static DWORD m_dwMultipleJumpDelay ;
	static bool m_bMultipleJump ;

public :
	CTilesWater() ;
	virtual ~CTilesWater() ;

	void Effect1(CDynamicObjects* pDynamicObject) ;
} ;