#include "Friends_Okulo.h"
#include "Effect_OkuloAbility.h"
#include "Effect_SparkImpact.h"
#include "Sprite.h"

#include "Effect_List.h"

CFriends_Okulo::CFriends_Okulo() : m_pEAbility(0)
{
}
CFriends_Okulo::~CFriends_Okulo()
{
	if(m_pEAbility!=0)
		delete m_pEAbility ;
}

void CFriends_Okulo::Init()
{
	LoadDat("Resource/Data/Friends/Okulo.dat") ;

	m_pEAbility = new CEffect_OkuloAbility ;
	m_pEAbility->Init() ;

	g_Effect_List->AddEffect(m_pEAbility) ;
}

void CFriends_Okulo::Update()
{
	if(!m_bRelease)
		return ;

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

void CFriends_Okulo::Render()
{
	m_pSprite->SetPosition(m_fX, m_fY) ;
	m_pESparkImpact->SetPosition(m_fX, m_fY) ;
	m_pEAbility->SetPosition(m_fX, m_fY) ;

	m_pSprite->Render() ;
	m_pESparkImpact->Render() ;
	m_pEAbility->Render() ;
}