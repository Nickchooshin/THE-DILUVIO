#include "Tiles_GroundEarthUp.h"
#include "Sprite.h"

CTiles_GroundEarthUp::CTiles_GroundEarthUp()
{
}
CTiles_GroundEarthUp::~CTiles_GroundEarthUp()
{
}

void CTiles_GroundEarthUp::Init()
{
	m_pSprite = new CSprite ;
	m_pSprite->Init(64.0f, 64.0f, "Resource/Image/Terrain/Ground_earth_up.png") ;

	SetBoundingBox() ;
}