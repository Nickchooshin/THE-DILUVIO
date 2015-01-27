#include "Tiles_JailLever.h"
#include "Sprite.h"

#include "D3dDevice.h"

CTiles_JailLever::CTiles_JailLever() : m_LinkIndex(-1, -1)
{
	m_bEffect = true ;
}
CTiles_JailLever::~CTiles_JailLever()
{
}

void CTiles_JailLever::Init()
{
	LoadDat("Resource/Data/Tiles/Jail_lever.dat") ;
}

void CTiles_JailLever::Effect1(CDynamicObjects* pDynamicObject)
{
	if(m_State==NORMAL)
	{
		m_State = EFFECT1 ;

		if(m_pLinkedTile!=NULL)
			m_pLinkedTile->Effect2(pDynamicObject) ;
	}
}

void CTiles_JailLever::Animation()
{
	// Animation Frame, Index
	int MaxFrame ;
	Position Index ;

	switch(m_State)
	{
	case NORMAL :
		MaxFrame = m_nTileFrame ;
		Index = m_Tile_Index ;
		break ;

	case EFFECT1 :
		MaxFrame = m_nEffect1Frame ;
		Index = m_Effect1_Index ;
		break ;

	case EFFECT2 :
		MaxFrame = m_nEffect2Frame ;
		Index = m_Effect2_Index ;
	}

	// Animation
	m_fAnimationTime += g_D3dDevice->GetTime() ;

	if(m_fAnimationTime>=0.2f || (m_State!=m_prevState))
	{
		if(m_State!=m_prevState)
		{
			m_nNowFrame = 0 ;
			m_fAnimationTime = 0.0f ;
		}

		float left, top, right, bottom ;
		left = (float)((Index.x + m_nNowFrame) * m_ImgSize.x) ;
		top = (float)((Index.y) * m_ImgSize.y) ;
		right = (float)((Index.x + m_nNowFrame+1) * m_ImgSize.x) ;
		bottom = (float)((Index.y+1) * m_ImgSize.y) ;

		m_pSprite->SetTextureUV(left, top, right, bottom) ;

		int Frame = (int)(m_fAnimationTime / 0.2f) ;
		m_fAnimationTime -= Frame * 0.2f ;
		Frame %= MaxFrame ;
		m_nNowFrame += Frame ;
		if(m_nNowFrame>=MaxFrame)
		{
			if(m_State!=EFFECT1)
			{
				m_nNowFrame = 0 ;
				m_State = NORMAL ;
			}
			else
				m_nNowFrame = MaxFrame-1 ;
		}
	}

	m_prevState = m_State ;
}