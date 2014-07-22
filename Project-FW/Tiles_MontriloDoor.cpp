#include "Tiles_MontriloDoor.h"
#include "Sprite.h"

CTiles_MontriloDoor::CTiles_MontriloDoor()
{
}
CTiles_MontriloDoor::~CTiles_MontriloDoor()
{
}

void CTiles_MontriloDoor::Init()
{
	m_pSprite = new CSprite ;
	m_pSprite->Init(64.0f, 64.0f, "Resource/Image/Terrain/Montrilo_door.png") ;

	SetBoundingBox() ;
}