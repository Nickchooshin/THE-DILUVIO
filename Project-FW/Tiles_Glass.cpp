#include "Tiles_Glass.h"
#include "Sprite.h"

#include "D3dDevice.h"
#include "MusicManager.h"

CTiles_Glass::CTiles_Glass() : m_bOkuloEffect(false),
							   m_bRecover(false), m_bAbleRecover(true),
							   m_bVisible(false),
							   m_pSEGlass(NULL)
{
}
CTiles_Glass::~CTiles_Glass()
{
}

void CTiles_Glass::Init()
{
	LoadDat("Resource/Data/Tiles/Glass.dat") ;

	m_pSEGlass = g_MusicManager->LoadMusic("Resource/Sound/SE_Glass.mp3", false, false) ;
}

void CTiles_Glass::Update()
{
	if(m_bUnVisible)
	{
		m_bCollision = false ;

		if(m_CollisionDirection==0)
			m_bAbleRecover = true ;
	}
	else
	{
		if((m_CollisionDirection & COLLISION_UP) == COLLISION_UP)
		{
			if(m_State==NORMAL)
				g_MusicManager->PlayMusic(m_pSEGlass, 2) ;

			m_State = EFFECT1 ;
			m_bVisible = true ;
		}
	}

	Animation() ;

	m_CollisionDirection = 0 ;
}

void CTiles_Glass::Effect1(CDynamicObjects* pDynamicObject)
{
	m_bAbleRecover = false ;
}

void CTiles_Glass::Render()
{
	if(m_bCollision && m_bVisible)
	{
		m_pSprite->SetPosition(m_fX, m_fY) ;
		m_pSprite->Render() ;
	}
}

void CTiles_Glass::SendEventMessage(char *EventMessage, void *pData)
{
	int len = strlen(EventMessage) ;

	if(len==5 && strcmp(EventMessage, "GLASS")==0)
	{
		m_bVisible = true ;

		m_bOkuloEffect = true ;
		if(!m_bRecover && m_bAbleRecover)
		{
			m_bCollision = true ;
			m_bUnVisible = false ;
		}
	}
}

void CTiles_Glass::EventClear()
{
	if(m_State!=EFFECT1)
		m_bVisible = false ;
	
	m_bRecover = m_bOkuloEffect ;
	m_bOkuloEffect = false ;
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
				m_bUnVisible = true ;
			m_nNowFrame = 0 ;
			m_State = NORMAL ;
		}
	}

	m_prevState = m_State ;
}