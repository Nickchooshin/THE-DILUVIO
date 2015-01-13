#pragma once

#include "Tiles.h"

class CTiles_Arrival : public CTiles
{
public :
	CTiles_Arrival() ;
	~CTiles_Arrival() ;

	void Init() ;
	
	void Effect1(CDynamicObjects* pDynamicObject) ;
} ;