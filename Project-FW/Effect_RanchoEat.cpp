#include "Effect_RanchoEat.h"
#include "Sprite.h"

#include "D3dDevice.h"

CEffect_RanchoEat::CEffect_RanchoEat() : m_pTarget(NULL)
{
}
CEffect_RanchoEat::~CEffect_RanchoEat()
{
}

void CEffect_RanchoEat::Init()
{
	LoadDat("Resource/Data/Effect/Rancho_eat_effect.dat") ;
}

void CEffect_RanchoEat::SetTarget(CObjects *pTarget)
{
	m_pTarget = pTarget ;
	SetPosition(m_pTarget->GetPositionX(), m_pTarget->GetPositionY()) ;
}

void CEffect_RanchoEat::Update()
{
	if(m_pTarget!=NULL)
		SetPosition(m_pTarget->GetPositionX(), m_pTarget->GetPositionY()) ;

	Animation() ;
}

void CEffect_RanchoEat::Effect(CObjects* pObject)
{
	pObject->SendEventMessage("RANCHO", this) ;
}

int CEffect_RanchoEat::GetAniFrame()
{
	return m_nNowFrame ;
}

void CEffect_RanchoEat::Animation()
{
	// Animation Frame, Index
	int MaxFrame ;
	Position Index ;

	switch(m_State)
	{
	case NORMAL :
		MaxFrame = m_nNormalFrame ;
		Index = m_Normal_Index ;
		break ;

	case EFFECT1 :
		MaxFrame = m_nEffect1Frame ;
		Index = m_Effect1_Index ;
		break ;

	case EFFECT2 :
		MaxFrame = m_nEffect2Frame ;
		Index = m_Effect2_Index ;
		break ;
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
			m_nNowFrame = 0 ;
			m_State = NORMAL ;
			m_bVisible = false ;
		}
	}

	m_prevState = m_State ;
}