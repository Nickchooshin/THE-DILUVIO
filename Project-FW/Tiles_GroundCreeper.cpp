#include "Tiles_GroundCreeper.h"
#include "Sprite.h"

CTiles_GroundCreeper::CTiles_GroundCreeper()
{
}
CTiles_GroundCreeper::~CTiles_GroundCreeper()
{
}

void CTiles_GroundCreeper::Init()
{
	m_pSprite = new CSprite ;
	m_pSprite->Init(64.0f, 64.0f, "Resource/Image/Terrain/Ground_creeper.png") ;

	SetBoundingBox() ;
}