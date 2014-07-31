#pragma once

#include "Tiles.h"

class CTiles_GroundWater : public CTiles
{
public :
	CTiles_GroundWater() ;
	~CTiles_GroundWater() ;

	void Init() ;

	void Effect1(CDynamicObjects* pDynamicObject) ;
} ;