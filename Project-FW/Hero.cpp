#include "Hero.h"
#include "Sprite.h"

#include "Keyboard.h"
#include "D3dDevice.h"

CHero::CHero() : m_fVecSpeed(2.0f), m_fVecJump(6.5f),
				 m_fVecAcc(0.0f), m_fVecGravity(-1.0f),
				 m_bJump(false),
				 m_vForce(),
				 m_bGravity(true)
{
}
CHero::~CHero()
{
}

void CHero::Init()
{
	m_pSprite = new CSprite ;
	//m_pSprite->Init(64.0f, 64.0f, "Resource/Image/collision.png") ;
	m_pSprite->Init(64.0f, 64.0f, "Resource/Image/Char/Main_character.png") ;
	m_pSprite->SetTextureUV(0.0f, 0.0f, 64.0f, 64.0f) ;
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

Vector CHero::GetForce()
{
	return m_vForce ;
}

void CHero::SetJump(bool bFlag)
{
	m_bJump = bFlag ;
}

void CHero::GravityAccReset()
{
	m_fVecAcc = 0.0f ;
}

void CHero::Gravity()
{
	m_fVecAcc += m_fVecGravity ;
	m_vForce.y = m_fVecAcc ;
	m_fY += m_vForce.y ;

	if(m_fY<0.0f)
	{
		m_fY = 0.0f ;
		SetJump(false) ;
		GravityAccReset() ;
	}
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

	m_vForce.x = 0.0f ;
	m_vForce.y = 0.0f ;

	if(g_Keyboard->IsButtonDown(DIK_LEFT))
		m_vForce.x -= fSpeed ;
	if(g_Keyboard->IsButtonDown(DIK_RIGHT))
		m_vForce.x += fSpeed ;

	if(!m_bJump && g_Keyboard->IsButtonDown(DIK_UP))
	{
		m_fVecAcc = m_fVecJump * fTime ;

		m_bJump = true ;
	}

	m_fX += m_vForce.x ;
}