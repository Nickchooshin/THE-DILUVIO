#include "Friends_Okulo.h"
#include "Effect_OkuloAbility.h"
#include "Effect_SparkImpact.h"
#include "Sprite.h"

#include "Effect_List.h"

#include "MusicManager.h"

CFriends_Okulo::CFriends_Okulo() : m_pEAbility(NULL)
{
}
CFriends_Okulo::~CFriends_Okulo()
{
	if(m_pEAbility!=NULL)
		delete m_pEAbility ;
}

void CFriends_Okulo::Init()
{
	LoadDat("Resource/Data/Friends/Okulo.dat") ;

	m_pEAbility = new CEffect_OkuloAbility ;
	m_pEAbility->Init() ;

	g_Effect_List->AddEffect(m_pEAbility) ;

	m_pSEAbility = g_MusicManager->LoadMusic("Resource/Sound/SE_FriendAbility.mp3", false, false) ;
}

void CFriends_Okulo::Update()
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
	if((m_cDynamicState & SPARK)!=UNDERWATER)
		m_bSESpark = false ;
	
	if(!m_bShock && (m_State==STAND))
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

	Animation() ;

	m_pESparkImpact->SetVisible(m_bShock) ;
	m_pESparkImpact->Update() ;
}

void CFriends_Okulo::Render()
{
	m_pSprite->SetPosition(m_fX, m_fY) ;
	m_pESparkImpact->SetPosition(m_fX, m_fY) ;
	m_pEAbility->SetPosition(m_fX, m_fY) ;

	m_pSprite->Render() ;
	m_pESparkImpact->Render() ;
	m_pEAbility->Render() ;
}