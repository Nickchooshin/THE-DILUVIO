#include "Tiles_Ground.h"
#include "Sprite.h"

CTilesGround::CTilesGround()
{
}
CTilesGround::~CTilesGround()
{
}

void CTilesGround::Init()
{
	m_pSprite = new CSprite ;
	m_pSprite->Init(64.0f, 64.0f, "Resource/Terrain/Ground_earth_tile_1.png") ;
	//m_pSprite->SetCenterPosition(1.0f, -1.0f) ;

	SetBoundingBox() ;
}