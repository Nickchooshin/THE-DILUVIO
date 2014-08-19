#include "Effect_RompoDash.h"
#include "Sprite.h"

#include "D3dDevice.h"

#include "Friends_List.h"
#include "MapTiles_List.h"

//
#include "DynamicObjects_List.h"

CEffect_RompoDash::CEffect_RompoDash() : m_cDirection(0),
										 m_pDashObject(NULL)
{
}
CEffect_RompoDash::~CEffect_RompoDash()
{
}

void CEffect_RompoDash::Init()
{
	switch(m_cDirection)
	{
	case 'L' :
		LoadDat("Resource/Data/Effect/Rompo_dash_effectL.dat") ;
		break ;

	case 'R' :
		LoadDat("Resource/Data/Effect/Rompo_dash_effectR.dat") ;
		break ;

	default :
		MessageBox(NULL, "Not Init CEffect_RompoDash Direction", "Error", MB_OK) ;
		break ;
	}
}

void CEffect_RompoDash::Init(char direction)
{
	if(direction>=97 && direction<=122)
		direction -= 32 ;
	m_cDirection = direction ;
	Init() ;
}

void CEffect_RompoDash::Dash()
{
	m_bVisible = true ;
	m_State = EFFECT1 ;

	if(m_cDirection=='L')
		m_pDashObject = NULL ;
}

void CEffect_RompoDash::Crash()
{
	m_State = EFFECT2 ;

	if(m_cDirection=='L')
		m_fX = (int)((m_fX + 64.0f) / 64.0f) * 64.0f ;
	else
		m_fX = (int)(m_fX / 64.0f) * 64.0f ;
	m_fY = (int)(m_fY / 64.0f) * 64.0f ;
}

void CEffect_RompoDash::Update()
{
	int x = (int)(m_fX / 64.0f) ;
	int y = (int)(m_fY / 64.0f) ;
	int length = 1 ;
	//int direction = 0 ;
	CObjects *pObject ;

	if(m_cDirection=='L')
	{
		if(m_pDashObject==NULL)
			m_pDashObject = (CObjects*)g_Friends_List->GetFriend(x, y) ;

		x = (int)((m_fX + 64.0f) / 64.0f) ;

		pObject = (CObjects*)g_DynamicObjects_List->GetMainChar() ;
		int px = (int)(pObject->GetPositionX() / 64.0f) ;
		int py = (int)(pObject->GetPositionY() / 64.0f) ;

		if(x-1==px && y==py)
			++length ;

		pObject = (CObjects*)g_Friends_List->GetFriend(x-length, y) ;
		if(pObject!=NULL && pObject!=m_pDashObject)
		{
			Crash() ;
		}
		else
		{
			pObject = (CObjects*)g_MapTiles_List->GetTile(x-length, y) ;
			if(pObject!=NULL)
			{
				Crash() ;
			}
		}
	}
	else if(m_cDirection=='R')
	{
		pObject = (CObjects*)g_DynamicObjects_List->GetMainChar() ;
		int px = (int)(pObject->GetPositionX() / 64.0f) ;
		int py = (int)(pObject->GetPositionY() / 64.0f) ;

		if(x+1==px && y==py)
			++length ;

		pObject = (CObjects*)g_Friends_List->GetFriend(x+length, y) ;
		if(pObject!=NULL)
		{
			Crash() ;
		}
		else
		{
			pObject = (CObjects*)g_MapTiles_List->GetTile(x+length, y) ;
			if(pObject!=NULL)
			{
				Crash() ;
			}
		}
	}

	/*pObject = (CObjects*)g_DynamicObjects_List->GetMainChar() ;
	int px = (int)(pObject->GetBoundingBox().right / 64.0f) ;
	int py = (int)(pObject->GetPositionY() / 64.0f) ;

	if(m_cDirection=='L')
		direction = -1 ;
	else if(m_cDirection=='R')
		direction = 1 ;

	if(x+direction==px && y==py)
		++length ;

	pObject = (CObjects*)g_Friends_List->GetFriend(x+(length*direction), y) ;
	if(pObject!=NULL)
	{
		Crash() ;
	}
	else
	{
		pObject = (CObjects*)g_MapTiles_List->GetTile(x+(length*direction), y) ;
		if(pObject!=NULL)
		{
			Crash() ;
		}
	}*/

	Move() ;
	Animation() ;
}

void CEffect_RompoDash::Effect(CObjects *pObject)
{
	if(m_State!=EFFECT2)
		pObject->SendEventMessage("ROMPO", this) ;
	else
		pObject->SendEventMessage("ROMPO_END", this) ;
}

void CEffect_RompoDash::Move()
{
	int direction=0 ;

	if(m_cDirection=='L')
		direction = -1 ;
	else if(m_cDirection=='R')
		direction = 1 ;

	if(m_State!=EFFECT2)
		m_fX += 6.0f * g_D3dDevice->GetMoveTime() * direction ;
}

void CEffect_RompoDash::Animation()
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

	if(m_fAnimationTime>=0.05f || (m_State!=m_prevState))
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

		int Frame = (int)(m_fAnimationTime / 0.05f) ;
		m_fAnimationTime -= Frame * 0.05f ;
		Frame %= MaxFrame ;
		m_nNowFrame += Frame ;
		if(m_nNowFrame>=MaxFrame)
		{
			m_nNowFrame = 0 ;
			if(m_State==EFFECT2)
			{
				m_bVisible = false ;
			}
			m_State = NORMAL ;
		}
	}

	m_prevState = m_State ;
}