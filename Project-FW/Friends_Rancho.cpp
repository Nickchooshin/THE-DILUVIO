#include "Friends_Rancho.h"
#include "Effect_RanchoEat.h"
#include "Effect_SparkImpact.h"
#include "Sprite.h"
#include "LoadManager.h"

#include "Effect_List.h"
#include "Friends_List.h"
#include "MapTiles_List.h"

#include "D3dDevice.h"
#include "MusicManager.h"

CFriends_Rancho::CFriends_Rancho() : m_pEAbilityL(NULL), m_pEAbilityR(NULL),
									 m_nEatFrame(0),
									 m_Eat_Index(0, 0),
									 m_AState(NONE), m_prevAState(NONE)
{
}
CFriends_Rancho::~CFriends_Rancho()
{
	if(m_pEAbilityL!=0)
		delete m_pEAbilityL ;

	if(m_pEAbilityR!=0)
		delete m_pEAbilityR ;
}

void CFriends_Rancho::Init()
{
	LoadRanchoDat() ;

	m_pEAbilityL = new CEffect_RanchoEat ;
	m_pEAbilityL->Init() ;
	m_pEAbilityR = new CEffect_RanchoEat ;
	m_pEAbilityR->Init() ;

	g_Effect_List->AddEffect(m_pEAbilityL) ;
	g_Effect_List->AddEffect(m_pEAbilityR) ;

	m_pSEAbility = g_MusicManager->LoadMusic("Resource/Sound/SE_Rancho.mp3", false, false) ;
}
 
void CFriends_Rancho::Update()
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

	bool bAbility = !m_bUnVisible && !m_bShock && (m_State==STAND) ;
	if(bAbility && !m_pEAbilityL->BeVisible() && !m_pEAbilityR->BeVisible())
	{
		int x = (int)(m_fX / 64.0f) ;
		int y = (int)(m_fY / 64.0f) ;

		Eat(x, y, 'R') ;
		Eat(x, y, 'L') ;

		if(m_bSEAbility)
			m_bSEAbility = false ;
		if(!m_bSEAbility && (m_pEAbilityL->BeVisible() || m_pEAbilityR->BeVisible()))
		{
			m_bSEAbility = true ;
			g_MusicManager->PlayMusic(m_pSEAbility, 2) ;
		}
	}
	
	if(m_pEAbilityL->BeVisible())
		m_pEAbilityL->Update() ;
	if(m_pEAbilityR->BeVisible())
		m_pEAbilityR->Update() ;

	m_pESparkImpact->SetVisible(m_bShock) ;
	m_pESparkImpact->Update() ;
}

void CFriends_Rancho::SendEventMessage(char *EventMessage, void *pData)
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
}

void CFriends_Rancho::Render()
{
	m_pSprite->SetPosition(m_fX, m_fY) ;
	m_pESparkImpact->SetPosition(m_fX, m_fY) ;

	m_pSprite->Render() ;
	m_pESparkImpact->Render() ;
	m_pEAbilityL->Render() ;
	m_pEAbilityR->Render() ;
}

void CFriends_Rancho::Eat(int x, int y, char cDirection)
{
	int direction=0 ;
	CEffect_RanchoEat *pEffect_RanchoEat ;

	if(cDirection>=97 && cDirection<=122)
		cDirection -= 32 ;

	if(cDirection=='L')
	{
		direction = -1 ;
		pEffect_RanchoEat = m_pEAbilityL ;
	}
	else if(cDirection=='R')
	{
		direction = 1 ;
		pEffect_RanchoEat = m_pEAbilityR ;
	}

	CFriends *pFriend ;

	pFriend = g_Friends_List->GetFriend(x+direction, y) ;
	if(pFriend!=NULL && pFriend->BeStand())
	{
		pEffect_RanchoEat->SetVisible(true) ;
		pEffect_RanchoEat->SetPosition((x+direction) * 64.0f, y * 64.0f) ;
		pFriend->SendEventMessage("RANCHO", pEffect_RanchoEat) ;

		m_AState = EAT ;
	}
}

void CFriends_Rancho::LoadRanchoDat()
{
	g_LoadManager->OpenDat("Resource/Data/Friends/Rancho.dat") ;

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
		else if(len==9 && strcmp(item, "EAT_FRAME")==0)
		{
			g_LoadManager->GetValue(m_nEatFrame) ;
		}
		else if(len==9 && strcmp(item, "EAT_INDEX")==0)
		{
			g_LoadManager->GetValue(m_Eat_Index.x) ;
			g_LoadManager->GetValue(m_Eat_Index.y) ;
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

void CFriends_Rancho::Animation()
{
	// Animation Frame, Index
	int MaxFrame ;
	Position Index ;

	switch(m_State)
	{
	case STAND :
		switch(m_AState)
		{
		case NONE :
			MaxFrame = m_nStandFrame ;
			Index = m_Stand_Index ;
			break ;

		case EAT :
			MaxFrame = m_nEatFrame ;
			Index = m_Eat_Index ;
			break ;
		}
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

	if(m_fAnimationTime>=0.1f || (m_State!=m_prevState) || (m_AState!=m_prevAState))
	{
		if(m_State!=m_prevState || m_AState!=m_prevAState)
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

				if(m_AState==EAT)
					m_AState = NONE ;
			}
			else
				m_nNowFrame = MaxFrame-1 ;
		}
	}

	m_prevState = m_State ;
	m_prevAState = m_AState ;
}