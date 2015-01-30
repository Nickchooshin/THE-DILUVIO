#include "Friends_Makzelo.h"
#include "Effect_MakzeloAbility.h"
#include "Effect_SparkImpact.h"
#include "Effect_RanchoEat.h"
#include "Sprite.h"

#include "Effect_List.h"

#include "MusicManager.h"

CFriends_Makzelo::CFriends_Makzelo() : m_pEAbility(NULL)
{
}
CFriends_Makzelo::~CFriends_Makzelo()
{
	if(m_pEAbility!=NULL)
		delete m_pEAbility ;
}

void CFriends_Makzelo::Init()
{
	LoadDat("Resource/Data/Friends/Makzelo.dat") ;

	m_pEAbility = new CEffect_MakzeloAbility ;
	m_pEAbility->Init() ;

	g_Effect_List->AddEffect(m_pEAbility) ;

	m_pSEAbility = g_MusicManager->LoadMusic("Resource/Sound/SE_FriendAbility.mp3", false, false) ;
}

void CFriends_Makzelo::Update()
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

	if(!m_bUnVisible && !m_bShock && (m_State==STAND))
	{
		m_pEAbility->SetVisible(true) ;
		m_pEAbility->SetPosition(m_fX, m_fY) ;
		m_pEAbility->Update() ;

		if(!m_bSEAbility)
		{
			m_bSEAbility = true ;
			g_MusicManager->PlayMusic(m_pSEAbility, 2) ;
		}
	}
	else
	{
		m_pEAbility->SetVisible(false) ;
		m_bSEAbility = false ;
	}

	m_pESparkImpact->SetVisible(m_bShock) ;
	m_pESparkImpact->Update() ;
}

void CFriends_Makzelo::SendEventMessage(char *EventMessage, void *pData)
{
	if(!m_bRelease)
		return ;

	int len = strlen(EventMessage) ;

	if(len==5 && strcmp(EventMessage, "SPARK")==0)
	{
		m_bShock = true ;
	}
	else if(len==11 && strcmp(EventMessage, "RESPIRATION")==0)
	{
		m_bRespiration = true ;
	}
	else if(len==10 && strcmp(EventMessage, "ROMPO_TEST")==0)
	{
		bool *bHit = (bool*)pData ;
		*bHit = true ;
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

void CFriends_Makzelo::Render()
{
	m_pSprite->SetPosition(m_fX, m_fY) ;
	m_pESparkImpact->SetPosition(m_fX, m_fY) ;
	m_pEAbility->SetPosition(m_fX, m_fY) ;

	m_pSprite->Render() ;
	m_pESparkImpact->Render() ;
	m_pEAbility->Render() ;
}