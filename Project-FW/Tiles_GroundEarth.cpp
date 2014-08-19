#include "Tiles_GroundEarth.h"
#include "Sprite.h"

#include "MapTiles_List.h"

#include "Effect.h"

CTiles_GroundEarth::CTiles_GroundEarth()
{
	m_bEdible = true ;
}
CTiles_GroundEarth::~CTiles_GroundEarth()
{
}

void CTiles_GroundEarth::Init()
{
	LoadDat("Resource/Data/Tiles/Ground_earth.dat") ;
}

void CTiles_GroundEarth::SendEventMessage(char *EventMessage, void *pData)
{
	int len = strlen(EventMessage) ;

	if(len==5 && strcmp(EventMessage, "BUSXO")==0)
	{
		g_MapTiles_List->DeleteTile(this) ;
	}
}