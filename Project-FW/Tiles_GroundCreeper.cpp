#include "Tiles_GroundCreeper.h"
#include "Sprite.h"

#include "DynamicObjects.h"

CTiles_GroundCreeper::CTiles_GroundCreeper()
{
	m_bMainCharNonCollision = true ;
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
	pDynamicObject->SendEventMessage("RELEASE_ABSORB_FALSE") ;
}

void CTiles_GroundCreeper::SendEventMessage(char *EventMessage, void *pData)
{
	int len = strlen(EventMessage) ;

	if(len==7 && strcmp(EventMessage, "CREEPER")==0)
	{
		m_bCollision = false ;
		m_bEffect = true ;
	}
}

void CTiles_GroundCreeper::EventClear()
{
	m_bCollision = true ;
	m_bEffect = false ;
}