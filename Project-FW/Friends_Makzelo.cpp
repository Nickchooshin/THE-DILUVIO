#include "Friends_Makzelo.h"
#include "Effect_MakzeloAbility.h"
#include "Effect_SparkImpact.h"
#include "Sprite.h"

#include "Effect_List.h"

CFriends_Makzelo::CFriends_Makzelo() : m_pEAbillty(0)
{
}
CFriends_Makzelo::~CFriends_Makzelo()
{
	if(m_pEAbillty!=0)
		delete m_pEAbillty ;
}

void CFriends_Makzelo::Init()
{
	LoadDat("Resource/Data/Friends/Makzelo.dat") ;

	m_pEAbillty = new CEffect_MakzeloAbility ;
	m_pEAbillty->Init() ;

	g_Effect_List->AddEffect(m_pEAbillty) ;
}

void CFriends_Makzelo::Update()
{
	if(!m_bRelease)
		return ;

	////
	/*bool b = !m_bShock & (m_State==STAND) ;
	m_pEAbillty->SetVisible(b) ;*/
	////

	Animation() ;
	//
	bool b = m_bRelease && !m_bShock & (m_State==STAND) ;
	m_pEAbillty->SetVisible(b) ;

	if(!m_bShock)
	{
		m_pEAbillty->Update() ;
		m_pEAbillty->SetPosition(m_fX, m_fY) ;
	}

	m_pESparkImpact->SetVisible(m_bShock) ;
	m_pESparkImpact->Update() ;
	m_bShock = false ;
}

void CFriends_Makzelo::Render()
{
	m_pSprite->SetPosition(m_fX, m_fY) ;
	m_pESparkImpact->SetPosition(m_fX, m_fY) ;
	m_pEAbillty->SetPosition(m_fX, m_fY) ;

	m_pSprite->Render() ;
	m_pESparkImpact->Render() ;
	m_pEAbillty->Render() ;
}