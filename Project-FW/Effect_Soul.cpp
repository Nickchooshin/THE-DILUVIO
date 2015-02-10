#include "Effect_Soul.h"
#include "Sprite.h"

#include "DynamicObjects_List.h"
#include "Hero.h"

#include "D3dDevice.h"

CEffect_Soul::CEffect_Soul()
{
}
CEffect_Soul::~CEffect_Soul()
{
}

void CEffect_Soul::Init()
{
	LoadDat("Resource/Data/Effect/Soul.dat") ;
	if(CHero::m_bExVersion)
		m_pSprite->SetTexture("Resource/Image/Effect/Soul_Ex.png") ;
}

void CEffect_Soul::SetDirection()
{
	Direction direction = ((CHero*)g_DynamicObjects_List->GetMainChar())->GetDirection() ;
	Position Index ;

	if(direction==LEFT)
	{
		m_State = EFFECT1 ;
		Index = m_Effect1_Index ;
	}
	else
	{
		m_State = EFFECT2 ;
		Index = m_Effect2_Index ;
	}

	float left, top, right, bottom ;
	left = (float)((Index.x) * m_ImgSize.x) ;
	top = (float)((Index.y) * m_ImgSize.y) ;
	right = (float)((Index.x+1) * m_ImgSize.x) ;
	bottom = (float)((Index.y+1) * m_ImgSize.y) ;

	m_pSprite->SetTextureUV(left, top, right, bottom) ;
}

void CEffect_Soul::SetAlpha(int nAlpha)
{
	m_pSprite->SetAlpha(nAlpha) ;
}

void CEffect_Soul::Update()
{
	Animation() ;
}

void CEffect_Soul::Render()
{
	m_pSprite->SetPosition(m_fX, m_fY) ;
	m_pSprite->Render() ;
}

void CEffect_Soul::Animation()
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