#include "Effect.h"
#include "Sprite.h"
#include "LoadManager.h"
#include <stdlib.h>

#include "Objects.h"

#include "D3dDevice.h"

CEffect::CEffect() : m_ImgSize(0, 0), m_ColSize(0, 0),
					 m_nNowFrame(0),
					 m_nEffectFrame(0),
					 m_Effect_Index(0, 0),
					 m_fAnimationTime(0.0f),
					 m_State(EFFECT), m_prevState(EFFECT)
{
}
CEffect::~CEffect()
{
}

void CEffect::Update()
{
	Animation() ;
}

void CEffect::Effect(CObjects* pObject)
{
}

void CEffect::LoadDat(char *filepath)
{
	g_LoadManager->OpenDat(filepath) ;

	char item[100] ;
	char image_path[100] ;

	while(g_LoadManager->GetItem(item))
	{
		int len = strlen(item) ;

		if(len==5 && strcmp(item, "IMAGE")==0)
		{
			g_LoadManager->GetString(image_path) ;
		}
		else if(len==4 && strcmp(item, "SIZE")==0)
		{
			g_LoadManager->GetValue(m_ImgSize.x) ;
			g_LoadManager->GetValue(m_ImgSize.y) ;
		}
		else if(len==16 && strcmp(item, "COLLISION_CIRCLE")==0)
		{
			char radius[100] ;
			g_LoadManager->GetString(radius) ;
			m_BoundingCircle.radius = (float)strtod(radius, NULL) ;
		}
		else if(len==12 && strcmp(item, "EFFECT_FRAME")==0)
		{
			g_LoadManager->GetValue(m_nEffectFrame) ;
		}
		else if(len==12 && strcmp(item, "EFFECT_INDEX")==0)
		{
			g_LoadManager->GetValue(m_Effect_Index.x) ;
			g_LoadManager->GetValue(m_Effect_Index.y) ;
		}
	}

	g_LoadManager->CloseDat() ;

	m_pSprite = new CSprite ;
	m_pSprite->Init((float)m_ImgSize.x, (float)m_ImgSize.y, image_path) ;
	m_pSprite->SetTextureUV((float)(m_Effect_Index.x * m_ImgSize.x), (float)(m_Effect_Index.y * m_ImgSize.y),
							(float)((m_Effect_Index.x+1) * m_ImgSize.x), (float)((m_Effect_Index.y+1) * m_ImgSize.y)) ;

	SetBoundingBox() ;
}

void CEffect::SetBoundingBox()
{
	m_BoundingBox.left = 0 ;
	m_BoundingBox.top = 0 ;
	m_BoundingBox.right = 0 ;
	m_BoundingBox.bottom = 0 ;
}

const Circle CEffect::GetBoundingCircle()
{
	Circle circle ;
	circle.pos.x = (int)m_fX ;
	circle.pos.y = (int)m_fY ;
	circle.radius = m_BoundingCircle.radius ;

	return circle ;
}

void CEffect::Animation()
{
	// Animation Frame, Index
	int MaxFrame ;
	Position Index ;

	switch(m_State)
	{
	case EFFECT :
		MaxFrame = m_nEffectFrame ;
		Index = m_Effect_Index ;
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

		int Frame = (int)(m_fAnimationTime / 0.2f) ;
		m_fAnimationTime -= Frame * 0.2f ;
		Frame %= MaxFrame ;
		m_nNowFrame += Frame ;
		m_nNowFrame %= MaxFrame ;

		float left, top, right, bottom ;
		left = (float)((Index.x + m_nNowFrame) * m_ImgSize.x) ;
		top = (float)((Index.y) * m_ImgSize.y) ;
		right = (float)((Index.x + m_nNowFrame+1) * m_ImgSize.x) ;
		bottom = (float)((Index.y+1) * m_ImgSize.y) ;

		m_pSprite->SetTextureUV(left, top, right, bottom) ;
	}

	m_prevState = m_State ;
}