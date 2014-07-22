#include "Tiles_JailTrap.h"
#include "Sprite.h"

CTiles_JailTrap::CTiles_JailTrap()
{
}
CTiles_JailTrap::~CTiles_JailTrap()
{
}

void CTiles_JailTrap::Init()
{
	m_pSprite = new CSprite ;
	m_pSprite->Init(64.0f, 64.0f, "Resource/Image/Terrain/Jail_trap.png") ;

	SetBoundingBox() ;
}