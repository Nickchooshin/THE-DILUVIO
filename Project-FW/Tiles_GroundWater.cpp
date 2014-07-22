#include "Tiles_GroundWater.h"
#include "Sprite.h"

CTiles_GroundWater::CTiles_GroundWater()
{
}
CTiles_GroundWater::~CTiles_GroundWater()
{
}

void CTiles_GroundWater::Init()
{
	m_pSprite = new CSprite ;
	m_pSprite->Init(64.0f, 64.0f, "Resource/Image/Terrain/Ground_water.png") ;

	SetBoundingBox() ;
}