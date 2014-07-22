#include "Tiles_GroundWaterUp.h"
#include "Sprite.h"

CTiles_GroundWaterUp::CTiles_GroundWaterUp()
{
}
CTiles_GroundWaterUp::~CTiles_GroundWaterUp()
{
}

void CTiles_GroundWaterUp::Init()
{
	m_pSprite = new CSprite ;
	m_pSprite->Init(64.0f, 64.0f, "Resource/Image/Terrain/Ground_water_up.png") ;

	SetBoundingBox() ;
}