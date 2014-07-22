#include "Tiles_JailButton.h"
#include "Sprite.h"

CTiles_JailButton::CTiles_JailButton()
{
}
CTiles_JailButton::~CTiles_JailButton()
{
}

void CTiles_JailButton::Init()
{
	m_pSprite = new CSprite ;
	m_pSprite->Init(64.0f, 64.0f, "Resource/Image/Terrain/Jail_button.png") ;

	SetBoundingBox() ;
}