#include "Friends_Rancho.h"
#include "Effect_RanchoEat.h"
#include "Effect_SparkImpact.h"
#include "Sprite.h"

#include "Effect_List.h"
#include "Friends_List.h"
#include "MapTiles_List.h"

CFriends_Rancho::CFriends_Rancho() : m_pEAbilityL(0), m_pEAbilityR(0)
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
	LoadDat("Resource/Data/Friends/Rancho.dat") ;

	m_pEAbilityL = new CEffect_RanchoEat ;
	m_pEAbilityL->Init() ;
	m_pEAbilityR = new CEffect_RanchoEat ;
	m_pEAbilityR->Init() ;

	g_Effect_List->AddEffect(m_pEAbilityL) ;
	g_Effect_List->AddEffect(m_pEAbilityR) ;
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

	bool b = !m_bUnVisible & !m_bShock & (m_State==STAND) ;
	if(b && !m_pEAbilityL->BeVisible() && !m_pEAbilityR->BeVisible())
	{
		int x = (int)(m_fX / 64.0f) ;
		int y = (int)(m_fY / 64.0f) ;

		Eat(x, y, 'R') ;
		Eat(x, y, 'L') ;
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
		if(!m_bUnVisible && m_State==STAND)
			m_bStun = true ;
	}
	else if(len==11 && strcmp(EventMessage, "RESPIRATION")==0)
	{
		m_bStun = false ;
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
	CObjects *pObject ;

	pFriend = g_Friends_List->GetFriend(x+direction, y) ;
	if(pFriend!=NULL && pFriend->BeStand())
	{
		pObject = g_Friends_List->GetFriend(x+(2*direction), y) ;
		if(pObject==NULL)
		{
			pObject = (CObjects*)g_MapTiles_List->GetTile(x+(2*direction), y) ;
			if(pObject==NULL)
			{
				pEffect_RanchoEat->SetVisible(true) ;
				pEffect_RanchoEat->SetPosition((x+direction) * 64.0f, y * 64.0f) ;
				pFriend->SendEventMessage("RANCHO", pEffect_RanchoEat) ;
			}
		}
	}
}