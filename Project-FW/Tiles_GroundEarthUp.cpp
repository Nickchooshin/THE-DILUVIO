#include "Tiles_GroundEarthUp.h"
#include "Sprite.h"

#include "MapTiles_List.h"

CTiles_GroundEarthUp::CTiles_GroundEarthUp()
{
	m_bEdible = true ;
}
CTiles_GroundEarthUp::~CTiles_GroundEarthUp()
{
}

void CTiles_GroundEarthUp::Init()
{
	LoadDat("Resource/Data/Tiles/Ground_earth_up.dat") ;
}

void CTiles_GroundEarthUp::SendEventMessage(char *EventMessage, void *pData)
{
	int len = strlen(EventMessage) ;

	if(len==5 && strcmp(EventMessage, "BUSXO")==0)
	{
		g_MapTiles_List->DeleteTile(this) ;
	}
}