#include "Friends_Rompo.h"
#include "Effect_RompoDash.h"
#include "Effect_SparkImpact.h"
#include "Sprite.h"

#include "Effect_List.h"
//
#include "D3dDevice.h"

CFriends_Rompo::CFriends_Rompo() : m_pEAbility(0)
{
}
CFriends_Rompo::~CFriends_Rompo()
{
	if(m_pEAbility!=0)
		delete m_pEAbility ;
}

void CFriends_Rompo::Init()
{
	LoadDat("Resource/Data/Friends/Rompo.dat") ;

	m_pEAbility = new CEffect_RompoDash ;
	m_pEAbility->Init() ;

	g_Effect_List->AddEffect(m_pEAbility) ;
}
 
void CFriends_Rompo::Update()
{
	if(!m_bRelease)
		return ;

	if(m_bStun)
		m_State = STUN ;

	Animation() ;
	//
	m_pESparkImpact->SetVisible(m_bShock) ;
	m_pESparkImpact->Update() ;

	//
	m_pEAbility->SetVisible(true) ;
	m_pEAbility->Update() ;
	m_pEAbility->SetPosition(m_pEAbility->GetPositionX() + (6.0f * g_D3dDevice->GetMoveTime()), m_pEAbility->GetPositionY()) ;
}

void CFriends_Rompo::Render()
{
	m_pSprite->SetPosition(m_fX, m_fY) ;
	m_pESparkImpact->SetPosition(m_fX, m_fY) ;
	m_pEAbility->SetPosition(m_fX, m_fY) ;

	m_pSprite->Render() ;
	m_pESparkImpact->Render() ;
	m_pEAbility->Render() ;
}