#include "Hero.h"
#include "Sprite.h"

#include "Keyboard.h"
#include "D3dDevice.h"

#include "LoadManager.h"

CHero::CHero() : m_fVecSpeed(2.0f), m_fVecJump(6.5f),
				 m_fVecAcc(0.0f), m_fVecGravity(-1.0f),
				 m_bJump(false),
				 m_vForce(),
				 m_bGravity(true),
				 m_ColSize(0, 0),
				 m_nStandFrame(0), m_nMoveFrame(0),
				 m_Stand_LeftIndex(0, 0), m_Stand_RightIndex(0, 0),
				 m_Move_LeftIndex(0, 0), m_Move_RightIndex(0, 0),
				 m_Direction(RIGHT), m_prevDirection(RIGHT)
{
}
CHero::~CHero()
{
}

void CHero::Init()
{
	g_LoadManager->OpenDat("Resource/Data/Char.dat") ;

	char item[100] ;
	char image_path[100] ;

	while(g_LoadManager->GetItem(item))
	{
		if(strcmp(item, "IMAGE")==0)
		{
			g_LoadManager->GetString(image_path) ;
		}
		else if(strcmp(item, "SIZE")==0)
		{
			g_LoadManager->GetValue(m_ImgSize.x) ;
			g_LoadManager->GetValue(m_ImgSize.y) ;
		}
		else if(strcmp(item, "COLLISION_BOX")==0)
		{
			g_LoadManager->GetValue(m_BoundingBox.left) ;
			g_LoadManager->GetValue(m_BoundingBox.top) ;
			g_LoadManager->GetValue(m_BoundingBox.right) ;
			g_LoadManager->GetValue(m_BoundingBox.bottom) ;
		}
		else if(strcmp(item, "STAND_FRAME")==0)
		{
			g_LoadManager->GetValue(m_nStandFrame) ;
		}
		else if(strcmp(item, "STAND_LEFT_INDEX")==0)
		{
			g_LoadManager->GetValue(m_Stand_LeftIndex.x) ;
			g_LoadManager->GetValue(m_Stand_LeftIndex.y) ;
		}
		else if(strcmp(item, "STAND_RIGHT_INDEX")==0)
		{
			g_LoadManager->GetValue(m_Stand_RightIndex.x) ;
			g_LoadManager->GetValue(m_Stand_RightIndex.y) ;
		}
		else if(strcmp(item, "MOVE_FRAME")==0)
		{
			g_LoadManager->GetValue(m_nMoveFrame) ;
		}
		else if(strcmp(item, "MOVE_LEFT_INDEX")==0)
		{
			g_LoadManager->GetValue(m_Move_LeftIndex.x) ;
			g_LoadManager->GetValue(m_Move_LeftIndex.y) ;
		}
		else if(strcmp(item, "MOVE_RIGHT_INDEX")==0)
		{
			g_LoadManager->GetValue(m_Move_RightIndex.x) ;
			g_LoadManager->GetValue(m_Move_RightIndex.y) ;
		}
	}

	g_LoadManager->CloseDat() ;

	m_pSprite = new CSprite ;
	m_pSprite->Init((float)m_ImgSize.x, (float)m_ImgSize.y, image_path) ;
	m_pSprite->SetTextureUV((float)(m_Stand_LeftIndex.x * m_ImgSize.x), (float)(m_Stand_LeftIndex.y * m_ImgSize.y),
							(float)((m_Stand_LeftIndex.x+1) * m_ImgSize.x), (float)((m_Stand_LeftIndex.y+1) * m_ImgSize.y)) ;
	//m_pSprite->SetPositionZ(0.4f) ;

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
	Animation() ;
}

void CHero::SetBoundingBox()
{
	// ÁÂ»ó´Ü ¿øÁ¡°ú, Áß¾Ó ¿øÁ¡ ÁÂÇ¥°è °£ÀÇ ÁÂÇ¥ º¸Á¤
	m_BoundingBox.left = -(m_ImgSize.x/2) + m_BoundingBox.left ;
	m_BoundingBox.top = (m_ImgSize.y/2) - m_BoundingBox.top ;
	m_BoundingBox.right = m_BoundingBox.right - (m_ImgSize.x/2) ;
	m_BoundingBox.bottom = -m_BoundingBox.bottom + (m_ImgSize.y/2) ;
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

void CHero::Animation()
{
	// Direction
	if(m_vForce.x<0)
	{
		m_Direction = LEFT_MOVE ;
	}
	else if(m_vForce.x>0)
	{
		m_Direction = RIGHT_MOVE ;
	}
	else
	{
		if(m_Direction==LEFT_MOVE)
			m_Direction = LEFT ;
		else if(m_Direction==RIGHT_MOVE)
			m_Direction = RIGHT ;
	}

	if(m_Direction!=m_prevDirection)
		m_nNowFrame = 0 ;

	// Animation Frame, Index
	int MaxFrame ;
	Position Index ;

	switch(m_Direction)
	{
	case LEFT :
		MaxFrame = m_nStandFrame ;
		Index = m_Stand_LeftIndex ;
		break ;

	case RIGHT :
		MaxFrame = m_nStandFrame ;
		Index = m_Stand_RightIndex ;
		break ;

	case LEFT_MOVE :
		MaxFrame = m_nMoveFrame ;
		Index = m_Move_LeftIndex ;
		break ;

	case RIGHT_MOVE :
		MaxFrame = m_nMoveFrame ;
		Index = m_Move_RightIndex ;
		break ;
	}

	// Animation
	static float fTime = 0.0f ;
	fTime += g_D3dDevice->GetTime() ;

	if(fTime>=0.1f)
	{
		int Frame = fTime / 0.2f ;
		fTime -= Frame * 0.2f ;
		Frame %= MaxFrame ;
		m_nNowFrame += Frame ;
		m_nNowFrame %= MaxFrame ;

		m_pSprite->SetTextureUV((float)(Index.x + m_nNowFrame) * m_ImgSize.x, (float)(Index.y) * m_ImgSize.y,
								(float)(Index.x + m_nNowFrame+1) * m_ImgSize.x, (float)(Index.y+1) * m_ImgSize.y) ;
	}

	m_prevDirection = m_Direction ;
}