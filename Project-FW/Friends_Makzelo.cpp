#include "Friends_Makzelo.h"
#include "Effect_MakzeloAbility.h"
#include "Effect_SparkImpact.h"
#include "Sprite.h"

#include "Effect_List.h"

CFriends_Makzelo::CFriends_Makzelo() : m_pEAbility(0)
{
}
CFriends_Makzelo::~CFriends_Makzelo()
{
	if(m_pEAbility!=0)
		delete m_pEAbility ;
}

void CFriends_Makzelo::Init()
{
	LoadDat("Resource/Data/Friends/Makzelo.dat") ;

	m_pEAbility = new CEffect_MakzeloAbility ;
	m_pEAbility->Init() ;

	g_Effect_List->AddEffect(m_pEAbility) ;
}

void CFriends_Makzelo::Update()
{
	if(!m_bRelease)
		return ;

	if(m_bStun)
		m_State = STUN ;

	Animation() ;
	//
	bool b = m_bRelease && !m_bShock & (m_State==STAND) ;
	m_pEAbility->SetVisible(b) ;

	if(!m_bShock)
	{
		m_pEAbility->Update() ;
		m_pEAbility->SetPosition(m_fX, m_fY) ;
	}

	m_pESparkImpact->SetVisible(m_bShock) ;
	m_pESparkImpact->Update() ;
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