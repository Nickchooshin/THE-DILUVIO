#include "Tiles_GroundStone.h"
#include "Sprite.h"

CTiles_GroundStone::CTiles_GroundStone()
{
}
CTiles_GroundStone::~CTiles_GroundStone()
{
}

void CTiles_GroundStone::Init()
{
	m_pSprite = new CSprite ;
	m_pSprite->Init(64.0f, 64.0f, "Resource/Image/Terrain/Ground_stone.png") ;

	SetBoundingBox() ;
}