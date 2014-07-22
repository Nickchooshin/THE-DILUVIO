#include "Tiles_GroundEarth.h"
#include "Sprite.h"

CTiles_GroundEarth::CTiles_GroundEarth()
{
}
CTiles_GroundEarth::~CTiles_GroundEarth()
{
}

void CTiles_GroundEarth::Init()
{
	m_pSprite = new CSprite ;
	m_pSprite->Init(64.0f, 64.0f, "Resource/Image/Terrain/Ground_earth.png") ;

	SetBoundingBox() ;
}