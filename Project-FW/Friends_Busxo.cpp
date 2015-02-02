#include "Friends_Busxo.h"
#include "Effect_BusxoAbility.h"
#include "Effect_SparkImpact.h"
#include "Sprite.h"
#include "LoadManager.h"

#include "Effect_List.h"
#include "MapTiles_List.h"
#include "Tiles.h"
#include "Friends_List.h"

#include "D3dDevice.h"
#include "MusicManager.h"

CFriends_Busxo::CFriends_Busxo() : m_pEAbility(NULL),
								   m_nStartEatFrame(0), m_nEatingFrame(0), m_nEndEatFrame(0),
								   m_Start_Eat_Index(0, 0), m_Eating_Index(0, 0), m_End_Eat_Index(0, 0),
								   m_AState(NONE), m_prevAState(NONE)
{
}
CFriends_Busxo::~CFriends_Busxo()
{
	if(m_pEAbility!=NULL)
		delete m_pEAbility ;
}

void CFriends_Busxo::Init()
{
	LoadBusxoDat() ;

	m_pEAbility = new CEffect_BusxoAbility ;
	m_pEAbility->Init() ;

	g_Effect_List->AddEffect(m_pEAbility) ;

	m_pSEAbility = g_MusicManager->LoadMusic("Resource/Sound/SE_Busxo.mp3", false, true) ;
}

void CFriends_Busxo::Absorb()
{
	if(m_State==STUN)
		return ;

	if(m_State!=RELEASE && m_AState==NONE)
		m_State = ABSORB ;
}

void CFriends_Busxo::Update()
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
	
	if((m_cDynamicState & UNDERWATER)!=UNDERWATER)
		m_bSEWater = false ;
	if((m_cDynamicState & SPARK)!=SPARK)
		m_bSESpark = false ;

	Animation() ;

	if(!m_bShock && (m_State==STAND))
	{
		// Busxo Ability
		if(m_AState==EATING)
		{
			m_pEAbility->SetVisible(true) ;
			m_pEAbility->SetPosition(m_fX, m_fY + m_BoundingBox.bottom - 1.0f) ;
			m_pEAbility->Update() ;
		}
		else
			m_pEAbility->SetVisible(false) ;

		if(m_State==STAND)
		{
			int x = (int)(m_fX / 64.0f) ;
			int y = (int)((m_fY + m_BoundingBox.top) / 64.0f) - 1 ;
			CTiles *pTile = g_MapTiles_List->GetTile(x, y) ;
			if(pTile!=NULL)
			{
				bool bEdible = pTile->BeEdible() ;

				if(bEdible && m_AState==NONE)
					m_AState = START_EAT ;
				else if(!bEdible && m_AState==EATING)
					m_AState = END_EAT ;
			}
			else
			{
				if(m_AState==EATING)
				{
					CFriends *pFriend = g_Friends_List->GetFriend(x, y) ;
					if(pFriend!=NULL)
						m_AState = END_EAT ;
				}
			}
		}
	}
	else
	{
		m_AState = NONE ;
		
		m_pEAbility->SetVisible(false) ;
	}

	if(m_pEAbility->BeVisible())
	{
		if(!m_bSEAbility)
		{
			m_bSEAbility = true ;
			g_MusicManager->PlayMusic(m_pSEAbility, 3) ;
		}
	}
	else if(m_bSEAbility)
	{
		m_bSEAbility = false ;
		g_MusicManager->StopMusic(3) ;
	}

	m_pESparkImpact->SetVisible(m_bShock) ;
	m_pESparkImpact->Update() ;
}

void CFriends_Busxo::LoadBusxoDat()
{
	g_LoadManager->OpenDat("Resource/Data/Friends/Busxo.dat") ;

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
		else if(len==15 && strcmp(item, "START_EAT_FRAME")==0)
		{
			g_LoadManager->GetValue(m_nStartEatFrame) ;
		}
		else if(len==15 && strcmp(item, "START_EAT_INDEX")==0)
		{
			g_LoadManager->GetValue(m_Start_Eat_Index.x) ;
			g_LoadManager->GetValue(m_Start_Eat_Index.y) ;
		}
		else if(len==12 && strcmp(item, "EATING_FRAME")==0)
		{
			g_LoadManager->GetValue(m_nEatingFrame) ;
		}
		else if(len==12 && strcmp(item, "EATING_INDEX")==0)
		{
			g_LoadManager->GetValue(m_Eating_Index.x) ;
			g_LoadManager->GetValue(m_Eating_Index.y) ;
		}
		else if(len==13 && strcmp(item, "END_EAT_FRAME")==0)
		{
			g_LoadManager->GetValue(m_nEndEatFrame) ;
		}
		else if(len==13 && strcmp(item, "END_EAT_INDEX")==0)
		{
			g_LoadManager->GetValue(m_End_Eat_Index.x) ;
			g_LoadManager->GetValue(m_End_Eat_Index.y) ;
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
	m_pSprite->SetTextureUV((float)(m_Stand_Index.x * m_ImgSize.x), (float)(m_Stand_Index.y * m_ImgSize.y),
							(float)((m_Stand_Index.x+1) * m_ImgSize.x), (float)((m_Stand_Index.y+1) * m_ImgSize.y)) ;

	SetBoundingBox() ;
}

void CFriends_Busxo::Animation()
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

		case START_EAT :
			MaxFrame = m_nStartEatFrame ;
			Index = m_Start_Eat_Index ;
			break ;

		case EATING :
			MaxFrame = m_nEatingFrame ;
			Index = m_Eating_Index ;
			break ;

		case END_EAT :
			MaxFrame = m_nEndEatFrame ;
			Index = m_End_Eat_Index ;
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

	//if(m_fAnimationTime>=0.1f || (m_State!=m_prevState))
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

				//
				if(m_AState==START_EAT)
					m_AState = EATING ;
				else if(m_AState==END_EAT)
					m_AState = NONE ;
			}
			else
				m_nNowFrame = MaxFrame-1 ;
		}
	}

	m_prevState = m_State ;
	m_prevAState = m_AState ;
}