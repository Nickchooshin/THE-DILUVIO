#include "Tiles_GroundCreeper.h"
#include "Sprite.h"

#include "DynamicObjects.h"

CTiles_GroundCreeper::CTiles_GroundCreeper()
{
}
CTiles_GroundCreeper::~CTiles_GroundCreeper()
{
}

void CTiles_GroundCreeper::Init()
{
	LoadDat("Resource/Data/Tiles/Ground_creeper.dat") ;
}

void CTiles_GroundCreeper::Effect1(CDynamicObjects* pDynamicObject)
{
	//pDynamicObject->SendEventMessage("
	//dont release absorb
}

void CTiles_GroundCreeper::SendEventMessage(char *EventMessage)
{
	int len = strlen(EventMessage) ;

	if(len==7 && strcmp(EventMessage, "CREEPER")==0)
		m_bCollision = false ;
}

void CTiles_GroundCreeper::EventClear()
{
	m_bCollision = true ;
}