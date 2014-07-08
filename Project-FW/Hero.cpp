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
				 m_ImgSize(0, 0), m_ColSize(0, 0),
				 m_nNowFrame(0),
				 m_nStandFrame(0), m_nMoveFrame(0), m_nJumpFrame(0), m_nAbsorbFrame(0), m_nReleaseFrame(0),
				 m_Stand_LeftIndex(0, 0), m_Stand_RightIndex(0, 0),
				 m_Move_LeftIndex(0, 0), m_Move_RightIndex(0, 0),
				 m_Jump_LeftIndex(0, 0), m_Jump_RightIndex(0, 0),
				 m_Absorb_LeftIndex(0, 0), m_Absorb_RightIndex(0, 0),
				 m_Release_LeftIndex(0, 0), m_Release_RightIndex(0, 0),
				 m_State(RIGHT), m_prevState(RIGHT)
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
		else if(strcmp(item, "JUMP_FRAME")==0)
		{
			g_LoadManager->GetValue(m_nJumpFrame) ;
		}
		else if(strcmp(item, "JUMP_LEFT_INDEX")==0)
		{
			g_LoadManager->GetValue(m_Jump_LeftIndex.x) ;
			g_LoadManager->GetValue(m_Jump_LeftIndex.y) ;
		}
		else if(strcmp(item, "JUMP_RIGHT_INDEX")==0)
		{
			g_LoadManager->GetValue(m_Jump_RightIndex.x) ;
			g_LoadManager->GetValue(m_Jump_RightIndex.y) ;
		}
		else if(strcmp(item, "ABSORB_LEFT_INDEX")==0)
		{
			g_LoadManager->GetValue(m_Absorb_LeftIndex.x) ;
			g_LoadManager->GetValue(m_Absorb_LeftIndex.y) ;
		}
		else if(strcmp(item, "ABSORB_RIGHT_INDEX")==0)
		{
			g_LoadManager->GetValue(m_Absorb_RightIndex.x) ;
			g_LoadManager->GetValue(m_Absorb_RightIndex.y) ;
		}
		else if(strcmp(item, "ABSORB_FRAME")==0)
		{
			g_LoadManager->GetValue(m_nAbsorbFrame) ;
		}
		else if(strcmp(item, "RELEASE_LEFT_INDEX")==0)
		{
			g_LoadManager->GetValue(m_Release_LeftIndex.x) ;
			g_LoadManager->GetValue(m_Release_LeftIndex.y) ;
		}
		else if(strcmp(item, "RELEASE_RIGHT_INDEX")==0)
		{
			g_LoadManager->GetValue(m_Release_RightIndex.x) ;
			g_LoadManager->GetValue(m_Release_RightIndex.y) ;
		}
		else if(strcmp(item, "RELEASE_FRAME")==0)
		{
			g_LoadManager->GetValue(m_nReleaseFrame) ;
		}
	}

	g_LoadManager->CloseDat() ;

	m_pSprite = new CSprite ;
	m_pSprite->Init((float)m_ImgSize.x, (float)m_ImgSize.y, image_path) ;
	m_pSprite->SetTextureUV((float)(m_Stand_RightIndex.x * m_ImgSize.x), (float)(m_Stand_RightIndex.y * m_ImgSize.y),
							(float)((m_Stand_RightIndex.x+1) * m_ImgSize.x), (float)((m_Stand_RightIndex.y+1) * m_ImgSize.y)) ;
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

void CHero::SetGravity(bool bFlag)
{
	m_bGravity = bFlag ;
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
	m_bGravity = true ;

	if(m_fY<0.0f)
	{
		m_fY = 0.0f ;
		m_bGravity = false ;
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
	// 좌상단 원점과, 중앙 원점 좌표계 간의 좌표 보정
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

	if(!m_bGravity && g_Keyboard->IsButtonDown(DIK_Z))
	{
		m_State = (State)((m_State / RIGHT) * RIGHT + LEFT_ABSORB) ;

		// 임시 주석 처리
		/*if(m_State==LEFT || m_State==LEFT_MOVE)
			m_State = LEFT_ABSORB ;
		else if(m_State==RIGHT || m_State==RIGHT_MOVE)
			m_State = RIGHT_ABSORB ;*/
	}
	else if(!m_bGravity && g_Keyboard->IsButtonDown(DIK_X))
	{
		m_State = (State)((m_State / RIGHT) * RIGHT + LEFT_RELEASE) ;
		
		// 임시 주석 처리
		/*if(m_State==LEFT)
			m_State = LEFT_RELEASE ;
		else if(m_State==RIGHT)
			m_State = RIGHT_RELEASE ;*/
	}
	else
	{
		m_State = (State)((m_State / RIGHT) * RIGHT + LEFT) ;
		
		// 임시 주석 처리
		/*if(m_State==LEFT_ABSORB || m_State==LEFT_RELEASE)
			m_State = LEFT ;
		else if(m_State==RIGHT_ABSORB || m_State==RIGHT_RELEASE)
			m_State = RIGHT ;*/

		if(g_Keyboard->IsButtonDown(DIK_LEFT))
			m_vForce.x -= fSpeed ;
		if(g_Keyboard->IsButtonDown(DIK_RIGHT))
			m_vForce.x += fSpeed ;

		if(!m_bJump && g_Keyboard->IsButtonDown(DIK_UP))
		{
			m_fVecAcc = m_fVecJump * fTime ;

			m_bJump = true ;
		}
	}

	m_fX += m_vForce.x ;
}

void CHero::Animation()
{
	// Direction
	//if(m_vForce.y!=0.0f || m_bGravity)
	if(m_bGravity)
	{
		if(m_vForce.x<0)
			m_State = LEFT_JUMP ;
		else if(m_vForce.x>0)
			m_State = RIGHT_JUMP ;
		else
		{
			m_State = (State)((m_State / RIGHT) * RIGHT + LEFT_JUMP) ;

			// 임시 주석 처리
			/*if(m_State==LEFT || m_State==LEFT_MOVE)
				m_State = LEFT_JUMP ;
			else if(m_State==RIGHT || m_State==RIGHT_MOVE)
				m_State = RIGHT_JUMP ;*/
		}
	}
	else if(m_vForce.x<0)
	{
		m_State = LEFT_MOVE ;
	}
	else if(m_vForce.x>0)
	{
		m_State = RIGHT_MOVE ;
	}
	else
	{
		State Temp = (State)(m_State % RIGHT) ;
		if(Temp==LEFT_MOVE || Temp==LEFT_JUMP)
			m_State = (State)((m_State / RIGHT) * RIGHT + LEFT) ;

		// 임시 주석 처리
		/*if(m_State==LEFT_MOVE || m_State==LEFT_JUMP)
			m_State = LEFT ;
		else if(m_State==RIGHT_MOVE || m_State==RIGHT_JUMP)
			m_State = RIGHT ;*/
	}

	if(m_State!=m_prevState)
		m_nNowFrame = 0 ;

	// Animation Frame, Index
	int MaxFrame ;
	Position Index ;

	switch(m_State)
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

	case LEFT_JUMP :
		MaxFrame = m_nJumpFrame ;
		Index = m_Jump_LeftIndex ;
		break ;
	case RIGHT_JUMP :
		MaxFrame = m_nJumpFrame ;
		Index = m_Jump_RightIndex ;
		break ;

	case LEFT_ABSORB :
		MaxFrame = m_nAbsorbFrame ;
		Index = m_Absorb_LeftIndex ;
		break ;
	case RIGHT_ABSORB :
		MaxFrame = m_nAbsorbFrame ;
		Index = m_Absorb_RightIndex ;
		break ;

	case LEFT_RELEASE :
		MaxFrame = m_nReleaseFrame ;
		Index = m_Release_LeftIndex ;
		break ;
	case RIGHT_RELEASE :
		MaxFrame = m_nReleaseFrame ;
		Index = m_Release_RightIndex ;
		break ;
	}

	// Animation
	static float fTime = 0.0f ;
	fTime += g_D3dDevice->GetTime() ;

	if(fTime>=0.2f)
	{
		int Frame = fTime / 0.2f ;
		fTime -= Frame * 0.2f ;
		Frame %= MaxFrame ;
		m_nNowFrame += Frame ;
		m_nNowFrame %= MaxFrame ;

		float left, top, right, bottom ;
		left = (float)((Index.x + m_nNowFrame) * m_ImgSize.x) ;
		top = (float)((Index.y) * m_ImgSize.y) ;
		right = (float)((Index.x + m_nNowFrame+1) * m_ImgSize.x) ;
		bottom = (float)((Index.y+1) * m_ImgSize.y) ;

		m_pSprite->SetTextureUV(left, top, right, bottom) ;
	}

	m_prevState = m_State ;
}