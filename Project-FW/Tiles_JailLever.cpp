#include "Tiles_JailLever.h"
#include "Sprite.h"

CTiles_JailLever::CTiles_JailLever() : m_LinkIndex(-1, -1)
{
}
CTiles_JailLever::~CTiles_JailLever()
{
}

void CTiles_JailLever::Init()
{
	LoadDat("Resource/Data/Tiles/Jail_lever.dat") ;
}

void CTiles_JailLever::Effect()
{
	m_State = EFFECT ;

	if(m_pLinkedTile!=NULL)
		m_pLinkedTile->Effect() ;
}