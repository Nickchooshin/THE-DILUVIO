#pragma once

#include "Tiles.h"

class CTiles_GroundCreeper : public CTiles
{
public :
	CTiles_GroundCreeper() ;
	~CTiles_GroundCreeper() ;

	void Init() ;
	
	void Effect1(CDynamicObjects* pDynamicObject) ;

	void SendEventMessage(char *EventMessage, void *pData) ;
	void EventClear() ;
} ;