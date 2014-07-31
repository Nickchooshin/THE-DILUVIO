#include "Tiles_JailTrap.h"
#include "Sprite.h"

#include "DynamicObjects.h"

#include "D3dDevice.h"

CTiles_JailTrap::CTiles_JailTrap() : m_bWork(false),
									 m_bDestory(false),
									 m_bConfined(false),
									 m_pTrappedObject(NULL),
									 m_nPulledCount(0)
{
}
CTiles_JailTrap::~CTiles_JailTrap()
{
}

void CTiles_JailTrap::Init()
{
	LoadDat("Resource/Data/Tiles/Jail_trap.dat") ;
}

void CTiles_JailTrap::Update()
{
	Animation() ;

	if(m_State==EFFECT1)
	{
		float x = m_pTrappedObject->GetPositionX() ;
		float y = m_pTrappedObject->GetPositionY() ;

		int Length = 45 - (m_nNowFrame * 15) ;
		float distance = abs(m_fX - x) ;

		if(distance>(float)Length)
		{
			if(x>m_fX)
				x = m_fX + (float)Length ;
			else if(x<m_fX)
				x = m_fX - (float)Length ;
		}

		if(m_fX==x && m_fY==y)
		{
			m_bConfined = true ;
			m_bCollision = true ;
		}

		if(m_bConfined)
		{
			x = m_fX ;
			y = m_fY ;
			m_pTrappedObject->GravityAccReset() ;
		}

		m_pTrappedObject->SetPosition(x, y) ;
	}

	m_CollisionDirection = 0 ;
}

void CTiles_JailTrap::Render()
{
	if(!m_bDestory)
	{
		m_pSprite->SetPosition(m_fX, m_fY) ;
		m_pSprite->Render() ;
	}
}

void CTiles_JailTrap::Effect1(CDynamicObjects* pDynamicObject)
{
	if(m_State==NORMAL)
	{
		m_State = EFFECT1 ;
		//m_bCollision = true ;
		m_bWork = true ;

		m_pTrappedObject = pDynamicObject ;
		//pDynamicObject->SetPosition(m_fX, m_fY) ;
	}
}

void CTiles_JailTrap::Effect2(CDynamicObjects* pDynamicObject)
{
	if(m_State!=EFFECT2)
	{
		m_State = EFFECT2 ;
		m_bCollision = false ;
	}
}

void CTiles_JailTrap::Animation()
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

		if(m_State==EFFECT2 && !m_bWork)
		{
			m_pSprite->SetAlpha(255 - (m_nNowFrame * 51)) ;
		}
		else
		{
			float left, top, right, bottom ;
			left = (float)((Index.x + m_nNowFrame) * m_ImgSize.x) ;
			top = (float)((Index.y) * m_ImgSize.y) ;
			right = (float)((Index.x + m_nNowFrame+1) * m_ImgSize.x) ;
			bottom = (float)((Index.y+1) * m_ImgSize.y) ;

			m_pSprite->SetTextureUV(left, top, right, bottom) ;
		}

		int Frame = (int)(m_fAnimationTime / 0.2f) ;
		m_fAnimationTime -= Frame * 0.2f ;
		Frame %= MaxFrame ;
		m_nNowFrame += Frame ;
		if(m_nNowFrame>=MaxFrame)
		{
			if(m_State!=EFFECT1 && m_State!=EFFECT2)
			{
				m_nNowFrame = 0 ;
				m_State = NORMAL ;
			}
			else
			{
				m_nNowFrame = MaxFrame-1 ;

				if(m_State==EFFECT2)
					m_bDestory = true ;
			}
		}
		m_nNowFrame %= MaxFrame ;
	}

	m_prevState = m_State ;
}