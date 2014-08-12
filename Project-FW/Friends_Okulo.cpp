#include "Friends_Okulo.h"
#include "Effect_OkuloAbility.h"
#include "Effect_SparkImpact.h"
#include "Sprite.h"

#include "Effect_List.h"

CFriends_Okulo::CFriends_Okulo() : m_pEAbillty(0)
{
}
CFriends_Okulo::~CFriends_Okulo()
{
	if(m_pEAbillty!=0)
		delete m_pEAbillty ;
}

void CFriends_Okulo::Init()
{
	LoadDat("Resource/Data/Friends/Okulo.dat") ;

	m_pEAbillty = new CEffect_OkuloAbility ;
	m_pEAbillty->Init() ;

	g_Effect_List->AddEffect(m_pEAbillty) ;
}

void CFriends_Okulo::Update()
{
	if(!m_bRelease)
		return ;

	////
	bool b = !m_bStun & (m_State==STAND) ;
	m_pEAbillty->SetVisible(b) ;
	////

	Animation() ;
	//
	if(!m_bStun)
	{
		m_pEAbillty->Update() ;
		m_pEAbillty->SetPosition(m_fX, m_fY) ;
	}

	m_pESparkImpact->SetVisible(m_bStun) ;
	m_pESparkImpact->Update() ;
	m_bStun = false ;
}

void CFriends_Okulo::Render()
{
	m_pSprite->SetPosition(m_fX, m_fY) ;
	m_pESparkImpact->SetPosition(m_fX, m_fY) ;
	m_pEAbillty->SetPosition(m_fX, m_fY) ;

	m_pSprite->Render() ;
	m_pESparkImpact->Render() ;
	m_pEAbillty->Render() ;
}