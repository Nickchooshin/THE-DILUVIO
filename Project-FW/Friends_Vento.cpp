#include "Friends_Vento.h"
#include "Sprite.h"
#include "Effect_VentoAbility.h"
#include "Effect_SparkImpact.h"

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

	m_pEAbillty->SetPosition(m_fX, m_fY) ;
}

void CFriends_Vento::Update()
{
	if(m_bRelease)
	{
		Animation() ;
		//
		m_pEAbillty->Update() ;
		m_pEAbillty->SetPosition(m_fX, m_fY) ;

		m_pESparkImpact->Update() ;
		m_bStun = false ;
	}
}

void CFriends_Vento::Render()
{
	m_pSprite->SetPosition(m_fX, m_fY) ;

	m_pSprite->Render() ;
	if(m_bStun)
	{
		m_pESparkImpact->SetPosition(m_fX, m_fY) ;
		m_pESparkImpact->Render() ;
	}
	else
	{
		m_pEAbillty->SetPosition(m_fX, m_fY) ;
		m_pEAbillty->Render() ;
	}
}