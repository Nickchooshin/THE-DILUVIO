#include "Hero.h"
#include "Sprite.h"

#include "Keyboard.h"
#include "D3dDevice.h"

CHero::CHero() : m_fVecSpeed(2.0f),
				 m_fVecAcc(0.0f), m_fVecGravity(-1.0f),
				 m_bJump(false)
{
}
CHero::~CHero()
{
}

void CHero::Init()
{
	m_pSprite = new CSprite ;
	m_pSprite->Init(64.0f, 64.0f, "Resource/collision.png") ;
	//m_pSprite->Init(64.0f, 64.0f, "Resource/Char/Main_character.png") ;
	//m_pSprite->SetTextureUV(0.0f, 0.0f, 32.0f, 32.0f) ;
	//m_pSprite->SetCenterPosition(0.5f, -1.0f) ;

	m_fX = 0.0f ;
	m_fY = 0.0f ;

	SetBoundingBox() ;
}

float CHero::GetPositionX()
{
	return m_fX ;
}

float CHero::GetPositionY()
{
	return m_fY ;
}

void CHero::GravityReset()
{
	m_bJump = false ;
	m_fVecAcc = 0.0f ;
	m_fY = 0.0f ;
}

void CHero::Update()
{
	Move() ;
}

void CHero::SetBoundingBox()
{
	m_BoundingBox.left = -32 ;
	m_BoundingBox.top = 32 ;
	m_BoundingBox.right = 32 ;
	m_BoundingBox.bottom = -32 ;
}

void CHero::Move()
{
	float fTime = g_D3dDevice->GetTime() ;
	float fSpeed = m_fVecSpeed * fTime ;

	if(g_Keyboard->IsButtonDown(DIK_LEFT))
		m_fX -= fSpeed ;
	if(g_Keyboard->IsButtonDown(DIK_RIGHT))
		m_fX += fSpeed ;

	if(!m_bJump && g_Keyboard->IsButtonDown(DIK_UP))
	{
		m_fVecAcc = 12.0f ;

		m_bJump = true ;
	}
	
	
	
	m_fVecAcc += m_fVecGravity ;
	m_fY += m_fVecAcc ;

	if(m_fY<0.0f)
		GravityReset() ;
}