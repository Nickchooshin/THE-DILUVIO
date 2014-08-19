#include "Friends_Vento.h"
#include "Effect_VentoAbility.h"
#include "Effect_SparkImpact.h"
#include "Sprite.h"

#include "Effect_List.h"

CFriends_Vento::CFriends_Vento() : m_pEAbility(0)
{
}
CFriends_Vento::~CFriends_Vento()
{
	if(m_pEAbility!=0)
		delete m_pEAbility ;
}

void CFriends_Vento::Init()
{
	LoadDat("Resource/Data/Friends/Vento.dat") ;

	m_pEAbility = new CEffect_VentoAbility ;
	m_pEAbility->Init() ;

	g_Effect_List->AddEffect(m_pEAbility) ;
}

void CFriends_Vento::Update()
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

	////
	bool b = !m_bShock & (m_State==STAND) ;
	m_pEAbility->SetVisible(b) ;
	////

	Animation() ;
	//
	if(!m_bShock)
	{
		m_pEAbility->Update() ;
		m_pEAbility->SetPosition(m_fX, m_fY) ;
	}

	m_pESparkImpact->SetVisible(m_bShock) ;
	m_pESparkImpact->Update() ;
}

void CFriends_Vento::Render()
{
	m_pSprite->SetPosition(m_fX, m_fY) ;
	m_pESparkImpact->SetPosition(m_fX, m_fY) ;
	m_pEAbility->SetPosition(m_fX, m_fY) ;

	m_pSprite->Render() ;
	m_pESparkImpact->Render() ;
	m_pEAbility->Render() ;
}