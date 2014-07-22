#include "Friends.h"
#include "Sprite.h"
#include "LoadManager.h"

#include "D3dDevice.h"

CFriends::CFriends() : m_ImgSize(0, 0), m_ColSize(0, 0),
					   m_nNowFrame(0),
					   m_nStandFrame(0), m_nAbsorbFrame(0), m_nReleaseFrame(0),
					   m_Stand_Index(0, 0), m_Absorb_Index(0, 0), m_Release_Index(0, 0),
					   m_Icon_Index(0, 0),
					   m_bRelease(false),
					   m_fAnimationTime(0.0f),
					   m_State(STAND), m_prevState(STAND)
{
	m_fVecGravity = -1.0f ;
}
CFriends::~CFriends()
{
}

void CFriends::Absorb()
{
	if(m_State!=RELEASE)
		m_State = ABSORB ;
}

void CFriends::Release()
{
	m_State = RELEASE ;
	m_bRelease = true ;
}

const bool CFriends::GetRelease()
{
	return m_bRelease ;
}

const Position CFriends::GetIconIndex()
{
	if(m_bRelease)
		return Position(0, 0) ;

	return m_Icon_Index ;
}

void CFriends::Update()
{
	if(m_bRelease)
		Animation() ;
}

void CFriends::LoadDat(char *filepath)
{
	g_LoadManager->OpenDat(filepath) ;

	char item[100] ;
	char image_path[100] ;

	while(g_LoadManager->GetItem(item))
	{
		if(strcmp(item, "IMAGE")==0)
		{
			g_LoadManager->GetString(image_path) ;
		}
		else if(strcmp(item, "SIZE")==0)
		{
			g_LoadManager->GetValue(m_ImgSize.x) ;
			g_LoadManager->GetValue(m_ImgSize.y) ;
		}
		else if(strcmp(item, "COLLISION_BOX")==0)
		{
			g_LoadManager->GetValue(m_BoundingBox.left) ;
			g_LoadManager->GetValue(m_BoundingBox.top) ;
			g_LoadManager->GetValue(m_BoundingBox.right) ;
			g_LoadManager->GetValue(m_BoundingBox.bottom) ;
		}
		else if(strcmp(item, "STAND_FRAME")==0)
		{
			g_LoadManager->GetValue(m_nStandFrame) ;
		}
		else if(strcmp(item, "STAND_INDEX")==0)
		{
			g_LoadManager->GetValue(m_Stand_Index.x) ;
			g_LoadManager->GetValue(m_Stand_Index.y) ;
		}
		else if(strcmp(item, "ABSORB_FRAME")==0)
		{
			g_LoadManager->GetValue(m_nAbsorbFrame) ;
		}
		else if(strcmp(item, "ABSORB_INDEX")==0)
		{
			g_LoadManager->GetValue(m_Absorb_Index.x) ;
			g_LoadManager->GetValue(m_Absorb_Index.y) ;
		}
		else if(strcmp(item, "RELEASE_FRAME")==0)
		{
			g_LoadManager->GetValue(m_nReleaseFrame) ;
		}
		else if(strcmp(item, "RELEASE_INDEX")==0)
		{
			g_LoadManager->GetValue(m_Release_Index.x) ;
			g_LoadManager->GetValue(m_Release_Index.y) ;
		}
		else if(strcmp(item, "ICON_INDEX")==0)
		{
			g_LoadManager->GetValue(m_Icon_Index.x) ;
			g_LoadManager->GetValue(m_Icon_Index.y) ;
		}
	}

	g_LoadManager->CloseDat() ;

	m_pSprite = new CSprite ;
	m_pSprite->Init((float)m_ImgSize.x, (float)m_ImgSize.y, image_path) ;
	m_pSprite->SetTextureUV((float)(m_Stand_Index.x * m_ImgSize.x), (float)(m_Stand_Index.y * m_ImgSize.y),
							(float)((m_Stand_Index.x+1) * m_ImgSize.x), (float)((m_Stand_Index.y+1) * m_ImgSize.y)) ;

	SetBoundingBox() ;
}

void CFriends::SetBoundingBox()
{
	m_BoundingBox.left = -(m_ImgSize.x/2) + m_BoundingBox.left ;
	m_BoundingBox.top = (m_ImgSize.y/2) - m_BoundingBox.top ;
	m_BoundingBox.right = m_BoundingBox.right - (m_ImgSize.x/2) ;
	m_BoundingBox.bottom = -m_BoundingBox.bottom + (m_ImgSize.y/2) ;
}

void CFriends::Animation()
{
	// Animation Frame, Index
	int MaxFrame ;
	Position Index ;

	switch(m_State)
	{
	case STAND :
		MaxFrame = m_nStandFrame ;
		Index = m_Stand_Index ;
		break ;

	case ABSORB :
		MaxFrame = m_nAbsorbFrame ;
		Index = m_Absorb_Index ;
		break ;

	case RELEASE :
		MaxFrame = m_nReleaseFrame ;
		Index = m_Release_Index ;
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
			// 흡수였을 경우, 캐릭터를 집어넣는다
			if(m_State==ABSORB)
			{
				m_bRelease = false ;
				GravityAccReset() ;
			}

			m_nNowFrame = 0 ;
			m_State = STAND ;
		}
		m_nNowFrame %= MaxFrame ;
	}

	m_prevState = m_State ;
}