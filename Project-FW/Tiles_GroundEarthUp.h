#pragma once

#include "Tiles.h"

class CTiles_GroundEarthUp : public CTiles
{
public :
	CTiles_GroundEarthUp() ;
	~CTiles_GroundEarthUp() ;

	void Init() ;

	void SendEventMessage(char *EventMessage) ;
} ;