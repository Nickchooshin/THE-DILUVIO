#include "Friends.h"
#include "Sprite.h"
#include "LoadManager.h"

#include "D3dDevice.h"

//
#include "Effect_SparkImpact.h"
#include "Effect_RanchoEat.h"

CFriends::CFriends() : m_pESparkImpact(NULL),
					   m_ImgSize(0, 0), m_ColSize(0, 0),
					   m_nNowFrame(0),
					   m_nStandFrame(0), m_nAbsorbFrame(0), m_nReleaseFrame(0), m_nStunFrame(0),
					   m_Stand_Index(0, 0), m_Absorb_Index(0, 0), m_Release_Index(0, 0), m_Stun_Index(0, 0),
					   m_Icon_Index(0, 0),
					   m_bEaten(false),
					   m_bRelease(false),
					   m_bStun(false), m_bShock(false),
					   m_bRespiration(false),
					   m_fAnimationTime(0.0f),
					   m_nRanchoAlpha(306),
					   m_bSEAbility(false),
					   m_pSEAbility(NULL),
					   m_State(STAND), m_prevState(STAND)
{
	m_fVecGravity = -0.3f ;

	m_pESparkImpact = new CEffect_SparkImpact() ;
	m_pESparkImpact->Init() ;
}
CFriends::~CFriends()
{
	if(m_pESparkImpact!=NULL)
		delete m_pESparkImpact ;
}

void CFriends::Absorb()
{
	if(m_State==STUN)
		return ;

	if(m_State!=RELEASE)
		m_State = ABSORB ;
}

void CFriends::Release()
{
	if(m_bEaten)
		return ;

	m_State = RELEASE ;
	m_bRelease = true ;
}

const bool CFriends::GetRelease()
{
	return m_bRelease ;
}

const Position CFriends::GetIconIndex()
{
	if(m_bRelease || m_bEaten)
		return Position(0, 0) ;

	return m_Icon_Index ;
}

const bool CFriends::BeStand()
{
	return (m_State==STAND) ;
}

void CFriends::Update()
{
	if(!m_bRelease)
		return ;

	// 흡수였을 경우, 캐릭터를 집어넣는다
	if(m_bUnVisible)
	{
		m_bUnVisible = false ;
		m_bRelease = false ;
		GravityAccReset() ;
		return ;
	}

	if(m_bStun)
		m_State = STUN ;

	Animation() ;

	m_pESparkImpact->SetVisible(m_bShock) ;
	m_pESparkImpact->Update() ;
}

void CFriends::SendEventMessage(char *EventMessage, void *pData)
{
	if(!m_bRelease)
		return ;

	int len = strlen(EventMessage) ;

	if(len==5 && strcmp(EventMessage, "SPARK")==0)
	{
		m_bShock = true ;
	}
	else if(len==5 && strcmp(EventMessage, "WATER")==0)
	{
		if(!m_bUnVisible && m_State==STAND && !m_bRespiration)
			m_bStun = true ;
	}
	else if(len==11 && strcmp(EventMessage, "RESPIRATION")==0)
	{
		m_bRespiration = true ;
	}
	else if(len==5 && strcmp(EventMessage, "ROMPO")==0)
	{
		CEffect *pEffect = (CEffect*)pData ;

		float fX = pEffect->GetPositionX() ;
		float fY = pEffect->GetPositionY() ;

		m_vForce.x = fX - m_fX ;
		m_vForce.y = fY - m_fY ;
		m_fX = fX ;
		m_fY = fY ;

		GravityAccReset() ;

		m_bStun = true ;
	}
	else if(len==9 && strcmp(EventMessage, "ROMPO_END")==0)
	{
		CEffect *pEffect = (CEffect*)pData ;

		float fX = pEffect->GetPositionX() ;
		float fY = pEffect->GetPositionY() ;

		m_vForce.x = fX - m_fX ;
		m_vForce.y = fY - m_fY ;
		m_fX = fX ;
		m_fY = fY ;

		GravityAccReset() ;

		m_bStun = false ;
		m_State = STAND ;
	}
	else if(len==6 && strcmp(EventMessage, "RANCHO")==0)
	{
		if(m_nRanchoAlpha!=0)
		{
			CEffect_RanchoEat *pEffect = (CEffect_RanchoEat*)pData ;

			m_nRanchoAlpha = 255 - (51 * pEffect->GetAniFrame()) ;
			m_pSprite->SetAlpha(m_nRanchoAlpha) ;

			m_bStun = true ;
		}
		else
		{
			m_bRelease = false ;
			m_bEaten = true ;
		}
	}
	else if(len==4 && strcmp(EventMessage, "MANO")==0)
	{
		bool *bHit = (bool*)pData ;
		*bHit = true ;

		m_bStun = true ;
	}
}

void CFriends::EventClear()
{
	m_bShock = false ;
	m_bRespiration = false ;
}

void CFriends::Render()
{
	m_pSprite->SetPosition(m_fX, m_fY) ;
	m_pESparkImpact->SetPosition(m_fX, m_fY) ;

	m_pSprite->Render() ;
	m_pESparkImpact->Render() ;
}

void CFriends::LoadDat(char *filepath)
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
		else if(len==13 && strcmp(item, "COLLISION_BOX")==0)
		{
			g_LoadManager->GetValue(m_BoundingBox.left) ;
			g_LoadManager->GetValue(m_BoundingBox.top) ;
			g_LoadManager->GetValue(m_BoundingBox.right) ;
			g_LoadManager->GetValue(m_BoundingBox.bottom) ;
		}
		else if(len==11 && strcmp(item, "STAND_FRAME")==0)
		{
			g_LoadManager->GetValue(m_nStandFrame) ;
		}
		else if(len==11 && strcmp(item, "STAND_INDEX")==0)
		{
			g_LoadManager->GetValue(m_Stand_Index.x) ;
			g_LoadManager->GetValue(m_Stand_Index.y) ;
		}
		else if(len==12 && strcmp(item, "ABSORB_FRAME")==0)
		{
			g_LoadManager->GetValue(m_nAbsorbFrame) ;
		}
		else if(len==12 && strcmp(item, "ABSORB_INDEX")==0)
		{
			g_LoadManager->GetValue(m_Absorb_Index.x) ;
			g_LoadManager->GetValue(m_Absorb_Index.y) ;
		}
		else if(len==13 && strcmp(item, "RELEASE_FRAME")==0)
		{
			g_LoadManager->GetValue(m_nReleaseFrame) ;
		}
		else if(len==13 && strcmp(item, "RELEASE_INDEX")==0)
		{
			g_LoadManager->GetValue(m_Release_Index.x) ;
			g_LoadManager->GetValue(m_Release_Index.y) ;
		}
		else if(len==10 && strcmp(item, "STUN_FRAME")==0)
		{
			g_LoadManager->GetValue(m_nStunFrame) ;
		}
		else if(len==10 && strcmp(item, "STUN_INDEX")==0)
		{
			g_LoadManager->GetValue(m_Stun_Index.x) ;
			g_LoadManager->GetValue(m_Stun_Index.y) ;
		}
		else if(len==10 && strcmp(item, "ICON_INDEX")==0)
		{
			g_LoadManager->GetValue(m_Icon_Index.x) ;
			g_LoadManager->GetValue(m_Icon_Index.y) ;
		}
	}

	g_LoadManager->CloseDat() ;

	m_pSprite = new CSprite ;
	m_pSprite->Init((float)m_ImgSize.x, (float)m_ImgSize.y, image_path) ;
	m_pSprite->SetTextureUV((float)(m_Release_Index.x * m_ImgSize.x), (float)(m_Release_Index.y * m_ImgSize.y),
							(float)((m_Release_Index.x+1) * m_ImgSize.x), (float)((m_Release_Index.y+1) * m_ImgSize.y)) ;

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

	case STUN :
		MaxFrame = m_nStunFrame ;
		Index = m_Stun_Index ;
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
		{
			if(m_State!=STUN)
			{
				// 흡수였을 경우, 캐릭터를 집어넣는다
				if(m_State==ABSORB)
					m_bUnVisible = true ;
				m_nNowFrame = 0 ;
				m_State = STAND ;
			}
			else
				m_nNowFrame = MaxFrame-1 ;
		}
	}

	m_prevState = m_State ;
}