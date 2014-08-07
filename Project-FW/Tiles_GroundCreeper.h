#pragma once

#include "Tiles.h"

class CTiles_GroundCreeper : public CTiles
{
public :
	CTiles_GroundCreeper() ;
	~CTiles_GroundCreeper() ;

	void Init() ;

	void SendEventMessage(char *EventMessage) ;
	void EventClear() ;
} ;