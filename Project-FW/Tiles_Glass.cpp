#include "Tiles_Glass.h"
#include "Sprite.h"

CTiles_Glass::CTiles_Glass()
{
}
CTiles_Glass::~CTiles_Glass()
{
}

void CTiles_Glass::Init()
{
	m_pSprite = new CSprite ;
	m_pSprite->Init(64.0f, 64.0f, "Resource/Image/Terrain/Glass.png") ;

	SetBoundingBox() ;
}