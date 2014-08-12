#include "Tiles_Glass.h"
#include "Sprite.h"

#include "D3dDevice.h"

CTiles_Glass::CTiles_Glass() : m_bVisible(false)
{
}
CTiles_Glass::~CTiles_Glass()
{
}

void CTiles_Glass::Init()
{
	LoadDat("Resource/Data/Tiles/Glass.dat") ;
}

void CTiles_Glass::Update()
{
	if(m_CollisionDirection & COLLISION_UP)
	{
		m_State = EFFECT1 ;
		m_bVisible = true ;
	}

	Animation() ;

	m_CollisionDirection = 0 ;
}

void CTiles_Glass::Render()
{
	if(m_bCollision && m_bVisible)
	{
		m_pSprite->SetPosition(m_fX, m_fY) ;
		m_pSprite->Render() ;
	}
}

void CTiles_Glass::SendEventMessage(char *EventMessage)
{
	int len = strlen(EventMessage) ;

	if(len==5 && strcmp(EventMessage, "GLASS")==0)
		m_bVisible = true ;
}

void CTiles_Glass::EventClear()
{
	if(m_State!=EFFECT1)
		m_bVisible = false ;
}

void CTiles_Glass::Animation()
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
			if(m_State==EFFECT1)
				m_bCollision = false ;
			m_nNowFrame = 0 ;
			m_State = NORMAL ;
		}
		m_nNowFrame %= MaxFrame ;
	}

	m_prevState = m_State ;
}