#include "Friends_Rompo.h"
#include "Effect_RompoDash.h"
#include "Effect_SparkImpact.h"
#include "Sprite.h"

#include "Effect_List.h"
#include "Friends_List.h"
#include "MapTiles_List.h"

#include "MusicManager.h"

CFriends_Rompo::CFriends_Rompo() : m_pEAbilityL(0), m_pEAbilityR(0),
								   m_pSEDash(NULL)
{
}
CFriends_Rompo::~CFriends_Rompo()
{
	if(m_pEAbilityL!=0)
		delete m_pEAbilityL ;

	if(m_pEAbilityR!=0)
		delete m_pEAbilityR ;
}

void CFriends_Rompo::Init()
{
	LoadDat("Resource/Data/Friends/Rompo.dat") ;

	m_pEAbilityL = new CEffect_RompoDash ;
	m_pEAbilityL->Init('L') ;
	m_pEAbilityR = new CEffect_RompoDash ;
	m_pEAbilityR->Init('R') ;

	g_Effect_List->AddEffect(m_pEAbilityL) ;
	g_Effect_List->AddEffect(m_pEAbilityR) ;
	
	m_pSEAbility = g_MusicManager->LoadMusic("Resource/Sound/SE_Rompo.mp3", false, false) ;
	m_pSEDash = g_MusicManager->LoadMusic("Resource/Sound/SE_Rompo_2.mp3", false, true) ;
}
 
void CFriends_Rompo::Update()
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

	bool bAbility = !m_bUnVisible && !m_bShock && (m_State==STAND) ;
	if(bAbility && !m_pEAbilityL->BeVisible() && !m_pEAbilityR->BeVisible())
	{
		const int x = (int)(m_fX / 64.0f) ;
		const int y = (int)(m_fY / 64.0f) ;
		 
		Dash(x, y, 'R') ;
		Dash(x, y, 'L') ;

		if(m_bSEAbility)
		{
			m_bSEAbility = false ;
			g_MusicManager->StopMusic(4) ;
		}
		if(!m_bSEAbility && (m_pEAbilityL->BeVisible() || m_pEAbilityR->BeVisible()))
		{
			m_bSEAbility = true ;
			g_MusicManager->PlayMusic(m_pSEAbility, 2) ;
			g_MusicManager->PlayMusic(m_pSEDash, 4) ;
		}
	}
	
	if(m_pEAbilityL->BeVisible())
		m_pEAbilityL->Update() ;
	if(m_pEAbilityR->BeVisible())
		m_pEAbilityR->Update() ;

	Animation() ;

	m_pESparkImpact->SetVisible(m_bShock) ;
	m_pESparkImpact->Update() ;
}

void CFriends_Rompo::Render()
{
	m_pSprite->SetPosition(m_fX, m_fY) ;
	m_pESparkImpact->SetPosition(m_fX, m_fY) ;

	m_pSprite->Render() ;
	m_pESparkImpact->Render() ;
	m_pEAbilityL->Render() ;
	m_pEAbilityR->Render() ;
}

void CFriends_Rompo::Dash(int x, int y, char cDirection)
{
	int direction=0 ;
	CEffect_RompoDash *pEffect_RompoDash ;

	if(cDirection>=97 && cDirection<=122)
		cDirection -= 32 ;

	if(cDirection=='L')
	{
		direction = -1 ;
		pEffect_RompoDash = m_pEAbilityL ;
	}
	else if(cDirection=='R')
	{
		direction = 1 ;
		pEffect_RompoDash = m_pEAbilityR ;
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
				pEffect_RompoDash->Dash() ;
				pEffect_RompoDash->SetPosition((x+direction) * 64.0f, y * 64.0f) ;
			}
		}
	}
}