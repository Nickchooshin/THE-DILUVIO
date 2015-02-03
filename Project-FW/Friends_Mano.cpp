#include "Friends_Mano.h"
#include "Effect_SparkImpact.h"
#include "Effect_RanchoEat.h"
#include "Sprite.h"
#include "LoadManager.h"

#include "Friends_List.h"

#include "DynamicObjects_List.h"
#include "Hero.h"

#include "D3dDevice.h"
#include "MusicManager.h"

#define m_Stand_LeftIndex	m_Stand_Index
#define m_Absorb_LeftIndex	m_Absorb_Index
#define m_Release_LeftIndex	m_Release_Index
#define m_Stun_LeftIndex	m_Stun_Index

CFriends_Mano::CFriends_Mano() : m_bUsingAbility(false),
								 m_nFaintFrame(0),
								 m_Stand_RightIndex(0, 0),
								 m_Absorb_RightIndex(0, 0),
								 m_Release_RightIndex(0, 0),
								 m_Stun_RightIndex(0, 0),
								 m_Faint_LeftIndex(0, 0), m_Faint_RightIndex(0, 0),
								 m_Direction(RIGHT),
								 m_AState(NONE), m_prevAState(NONE)
{
}
CFriends_Mano::~CFriends_Mano()
{
}

void CFriends_Mano::Init()
{
	LoadManoDat() ;
	
	m_pSEAbility = g_MusicManager->LoadMusic("Resource/Sound/SE_Mano.mp3", false, false) ;
}

void CFriends_Mano::Absorb()
{
	if(m_State==STUN || m_bUsingAbility)
		return ;

	if(m_State!=RELEASE)
		m_State = ABSORB ;
}

void CFriends_Mano::Release()
{
	if(m_bEaten)
		return ;

	m_State = RELEASE ;
	m_bRelease = true ;

	m_Direction = ((CHero*)g_DynamicObjects_List->GetMainChar())->GetDirection() ;
}

void CFriends_Mano::Update()
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

	if(!m_bUnVisible & !m_bShock & (m_State==STAND && m_AState==NONE))
	{
		int x = (int)(m_fX / 64.0f) ;
		int y = (int)(m_fY / 64.0f) ;

		m_bUsingAbility = false ;
		 
		Faint(x, y) ;
	}

	m_pESparkImpact->SetVisible(m_bShock) ;
	m_pESparkImpact->Update() ;
}

void CFriends_Mano::SendEventMessage(char *EventMessage, void *pData)
{
	if(!m_bRelease)
		return ;

	int len = strlen(EventMessage) ;

	if(len==5 && strcmp(EventMessage, "SPARK")==0)
	{
		m_cDynamicState |= SPARK ;

		if(!m_bSESpark)
		{
			m_bSESpark = true ;
			g_MusicManager->PlayMusic(m_pSESpark, 2) ;
		}

		m_bShock = true ;
	}
	else if(len==5 && strcmp(EventMessage, "WATER")==0)
	{
		m_cDynamicState |= UNDERWATER ;

		if(!m_bSEWater)
		{
			g_MusicManager->PlayMusic(m_pSEWater, 2) ;
			m_bSEWater = true ;
		}

		if(!m_bUnVisible && m_State==STAND && !m_bRespiration)
			m_bStun = true ;
	}
	else if(len==11 && strcmp(EventMessage, "RESPIRATION")==0)
	{
		m_bRespiration = true ;
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
}

void CFriends_Mano::Faint(int x, int y)
{
	int direction[2] = {-1, 1} ;
	int index = 0 ;

	if(m_Direction==RIGHT)
		index = 1 ;

	CFriends *pFriend ;

	for(int i=0; i<2; i++, index=(index+1)%2)
	{
		pFriend = g_Friends_List->GetFriend(x+direction[index], y) ;
		if(pFriend!=NULL && pFriend->BeStand())
		{
			bool bHit=false ;
			pFriend->SendEventMessage("MANO", &bHit) ;

			if(bHit)
			{
				m_Direction = (Direction)index ;
				m_AState = FAINT ;
				m_bUsingAbility = true ;

				g_MusicManager->PlayMusic(m_pSEAbility, 2) ;
			}

			return ;
		}
	}
}

void CFriends_Mano::LoadManoDat()
{
	g_LoadManager->OpenDat("Resource/Data/Friends/Mano.dat") ;

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
		else if(len==16 && strcmp(item, "STAND_LEFT_INDEX")==0)
		{
			g_LoadManager->GetValue(m_Stand_LeftIndex.x) ;
			g_LoadManager->GetValue(m_Stand_LeftIndex.y) ;
		}
		else if(len==17 && strcmp(item, "STAND_RIGHT_INDEX")==0)
		{
			g_LoadManager->GetValue(m_Stand_RightIndex.x) ;
			g_LoadManager->GetValue(m_Stand_RightIndex.y) ;
		}
		else if(len==12 && strcmp(item, "ABSORB_FRAME")==0)
		{
			g_LoadManager->GetValue(m_nAbsorbFrame) ;
		}
		else if(len==17 && strcmp(item, "ABSORB_LEFT_INDEX")==0)
		{
			g_LoadManager->GetValue(m_Absorb_LeftIndex.x) ;
			g_LoadManager->GetValue(m_Absorb_LeftIndex.y) ;
		}
		else if(len==18 && strcmp(item, "ABSORB_RIGHT_INDEX")==0)
		{
			g_LoadManager->GetValue(m_Absorb_RightIndex.x) ;
			g_LoadManager->GetValue(m_Absorb_RightIndex.y) ;
		}
		else if(len==13 && strcmp(item, "RELEASE_FRAME")==0)
		{
			g_LoadManager->GetValue(m_nReleaseFrame) ;
		}
		else if(len==18 && strcmp(item, "RELEASE_LEFT_INDEX")==0)
		{
			g_LoadManager->GetValue(m_Release_LeftIndex.x) ;
			g_LoadManager->GetValue(m_Release_LeftIndex.y) ;
		}
		else if(len==19 && strcmp(item, "RELEASE_RIGHT_INDEX")==0)
		{
			g_LoadManager->GetValue(m_Release_RightIndex.x) ;
			g_LoadManager->GetValue(m_Release_RightIndex.y) ;
		}
		else if(len==10 && strcmp(item, "STUN_FRAME")==0)
		{
			g_LoadManager->GetValue(m_nStunFrame) ;
		}
		else if(len==15 && strcmp(item, "STUN_LEFT_INDEX")==0)
		{
			g_LoadManager->GetValue(m_Stun_LeftIndex.x) ;
			g_LoadManager->GetValue(m_Stun_LeftIndex.y) ;
		}
		else if(len==16 && strcmp(item, "STUN_RIGHT_INDEX")==0)
		{
			g_LoadManager->GetValue(m_Stun_RightIndex.x) ;
			g_LoadManager->GetValue(m_Stun_RightIndex.y) ;
		}
		else if(len==11 && strcmp(item, "FAINT_FRAME")==0)
		{
			g_LoadManager->GetValue(m_nFaintFrame) ;
		}
		else if(len==16 && strcmp(item, "FAINT_LEFT_INDEX")==0)
		{
			g_LoadManager->GetValue(m_Faint_LeftIndex.x) ;
			g_LoadManager->GetValue(m_Faint_LeftIndex.y) ;
		}
		else if(len==17 && strcmp(item, "FAINT_RIGHT_INDEX")==0)
		{
			g_LoadManager->GetValue(m_Faint_RightIndex.x) ;
			g_LoadManager->GetValue(m_Faint_RightIndex.y) ;
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
	m_pSprite->SetTextureUV((float)(m_Release_RightIndex.x * m_ImgSize.x), (float)(m_Release_RightIndex.y * m_ImgSize.y),
							(float)((m_Release_RightIndex.x+1) * m_ImgSize.x), (float)((m_Release_RightIndex.y+1) * m_ImgSize.y)) ;

	SetBoundingBox() ;
}

void CFriends_Mano::Animation()
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
			if(m_Direction==LEFT)
				Index = m_Stand_LeftIndex ;
			else
				Index = m_Stand_RightIndex ;
			break ;

		case FAINT :
			MaxFrame = m_nFaintFrame ;
			if(m_Direction==LEFT)
				Index = m_Faint_LeftIndex ;
			else
				Index = m_Faint_RightIndex ;
			break ;
		}
		break ;

	case ABSORB :
		MaxFrame = m_nAbsorbFrame ;
		if(m_Direction==LEFT)
			Index = m_Absorb_LeftIndex ;
		else
			Index = m_Absorb_RightIndex ;
		break ;

	case RELEASE :
		MaxFrame = m_nReleaseFrame ;
		if(m_Direction==LEFT)
			Index = m_Release_LeftIndex ;
		else
			Index = m_Release_RightIndex ;
		break ;

	case STUN :
		MaxFrame = m_nStunFrame ;
		if(m_Direction==LEFT)
			Index = m_Stun_LeftIndex ;
		else
			Index = m_Stun_RightIndex ;
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

				if(m_AState==FAINT)
					m_AState = NONE ;
			}
			else
				m_nNowFrame = MaxFrame-1 ;
		}
	}

	m_prevState = m_State ;
	m_prevAState = m_AState ;
}