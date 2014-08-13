#include "Friends_Vento.h"
#include "Effect_VentoAbility.h"
#include "Effect_SparkImpact.h"
#include "Sprite.h"

#include "Effect_List.h"

CFriends_Vento::CFriends_Vento() : m_pEAbillty(0)
{
}
CFriends_Vento::~CFriends_Vento()
{
	if(m_pEAbillty!=0)
		delete m_pEAbillty ;
}

void CFriends_Vento::Init()
{
	LoadDat("Resource/Data/Friends/Vento.dat") ;

	m_pEAbillty = new CEffect_VentoAbility ;
	m_pEAbillty->Init() ;

	g_Effect_List->AddEffect(m_pEAbillty) ;
}

void CFriends_Vento::Update()
{
	if(!m_bRelease)
		return ;

	if(m_bStun)
		m_State = STUN ;

	////
	bool b = !m_bShock & (m_State==STAND) ;
	m_pEAbillty->SetVisible(b) ;
	////

	Animation() ;
	//
	if(!m_bShock)
	{
		m_pEAbillty->Update() ;
		m_pEAbillty->SetPosition(m_fX, m_fY) ;
	}

	m_pESparkImpact->SetVisible(m_bShock) ;
	m_pESparkImpact->Update() ;
	m_bShock = false ;
}

void CFriends_Vento::Render()
{
	m_pSprite->SetPosition(m_fX, m_fY) ;
	m_pESparkImpact->SetPosition(m_fX, m_fY) ;
	m_pEAbillty->SetPosition(m_fX, m_fY) ;

	m_pSprite->Render() ;
	m_pESparkImpact->Render() ;
	m_pEAbillty->Render() ;
}