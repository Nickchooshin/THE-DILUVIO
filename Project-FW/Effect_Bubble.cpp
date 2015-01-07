#include "Effect_Bubble.h"
#include "Sprite.h"

#include "DynamicObjects_List.h"
#include "Hero.h"

#include "D3dDevice.h"

CEffect_Bubble::CEffect_Bubble()
{
}
CEffect_Bubble::~CEffect_Bubble()
{
}

void CEffect_Bubble::Init()
{
	LoadDat("Resource/Data/Effect/Bubble.dat") ;
}

void CEffect_Bubble::SetDirection()
{
	Direction direction = ((CHero*)g_DynamicObjects_List->GetMainChar())->GetDirection() ;

	if(direction==LEFT)
		m_State = EFFECT1 ;
	else
		m_State = EFFECT2 ;
}

void CEffect_Bubble::Update()
{
	Animation() ;
}

void CEffect_Bubble::Render()
{
	m_pSprite->SetPosition(m_fX, m_fY) ;
	m_pSprite->Render() ;
}

void CEffect_Bubble::Animation()
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

	if(m_fAnimationTime>=0.1f || (m_State!=m_prevState))
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

		int Frame = (int)(m_fAnimationTime / 0.1f) ;
		m_fAnimationTime -= Frame * 0.1f ;
		Frame %= MaxFrame ;
		m_nNowFrame += Frame ;
		if(m_nNowFrame>=MaxFrame)
			m_nNowFrame = 0 ;
	}

	m_prevState = m_State ;
}