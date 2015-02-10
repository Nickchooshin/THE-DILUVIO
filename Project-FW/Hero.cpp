#include "Hero.h"
#include "Sprite.h"
#include "FriendChange_UI.h"
#include "Effect_Bubble.h"
#include "Effect_Soul.h"

#include "Friends_List.h"
#include "Friends.h"
#include "MapTiles_List.h"

#include "StageProgress.h"

#include "Keyboard.h"
#include "D3dDevice.h"

#include "LoadManager.h"
#include "MusicManager.h"

CHero::CHero() : m_ImgSize(0, 0),
				 m_nNowFrame(0),
				 m_nStandFrame(0), m_nMoveFrame(0), m_nJumpFrame(0), m_nAbsorbFrame(0), m_nReleaseFrame(0),
				 m_Stand_LeftIndex(0, 0), m_Stand_RightIndex(0, 0),
				 m_Move_LeftIndex(0, 0), m_Move_RightIndex(0, 0),
				 m_Jump_LeftIndex(0, 0), m_Jump_RightIndex(0, 0),
				 m_Absorb_LeftIndex(0, 0), m_Absorb_RightIndex(0, 0),
				 m_Release_LeftIndex(0, 0), m_Release_RightIndex(0, 0),
				 m_fTime(0.0f), m_fAnimationTime(0.0f),
				 m_State(RIGHT), m_prevState(RIGHT),
				 m_bDeath(false), m_bReleaseAbsorb(true), m_bRespiration(false),
				 m_Dying(SINK),
				 m_pFC_UI(NULL),
				 m_pEffect_Bubble(NULL), m_pEffect_Soul(NULL),
				 m_bSEWater(false),
				 m_pSEJump(NULL), m_pSESkill(NULL), m_pSEWater(NULL)
{
	m_fVecSpeed = 2.5f ;
	m_fVecJump = 7.5f ;

	//m_fVecGravity = -1.0f ;
	m_fVecGravity = -0.3f ;
}
CHero::~CHero()
{
	if(m_pFC_UI!=NULL)
		delete m_pFC_UI ;

	if(m_pEffect_Bubble!=NULL)
		delete m_pEffect_Bubble ;

	if(m_pEffect_Soul!=NULL)
		delete m_pEffect_Soul ;
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

	SetBoundingBox() ;

	m_pFC_UI = new CFriendChange_UI ;
	m_pFC_UI->Init() ;

	m_pEffect_Bubble = new CEffect_Bubble ;
	m_pEffect_Bubble->Init() ;

	m_pEffect_Soul = new CEffect_Soul ;
	m_pEffect_Soul->Init() ;

	m_pSEJump = g_MusicManager->LoadMusic("Resource/Sound/SE_Jump.mp3", false, false) ;
	m_pSESkill = g_MusicManager->LoadMusic("Resource/Sound/SE_Skill.mp3", false, true) ;
	m_pSEWater = g_MusicManager->LoadMusic("Resource/Sound/SE_Water.mp3", false, false) ;
}

CObjects::Direction CHero::GetDirection()
{
	return (Direction)(m_State / RIGHT) ;
}

void CHero::Update()
{
	if(m_bDeath)
	{
		Death() ;
		return ;
	}
	
	if((m_cDynamicState & UNDERWATER)!=UNDERWATER)
		m_bSEWater = false ;

	Move() ;
	Animation() ;

	m_bReleaseAbsorb = true ;

	m_pFC_UI->Update() ;
}

void CHero::Render()
{
	if(!m_bDeath)
	{
		m_pFC_UI->SetPosition(m_fX, m_fY) ;
		m_pFC_UI->Render_Behind() ;
	}

	if(m_Dying<SOUL_OUT)
	{
		m_pSprite->SetPosition(m_fX, m_fY) ;
		m_pSprite->Render() ;

		if(m_Dying==BUBBLE)
		{
			m_pEffect_Bubble->SetPosition(m_fX, m_fY) ;
			m_pEffect_Bubble->Render() ;
		}
	}
	else
		m_pEffect_Soul->Render() ;

	if(!m_bDeath)
		m_pFC_UI->Render_Front() ;
}

void CHero::SendEventMessage(char *EventMessage, void *pData)
{
	int len = strlen(EventMessage) ;

	if(len==20 && strcmp(EventMessage, "RELEASE_ABSORB_FALSE")==0)
	{
		m_bReleaseAbsorb = false ;
	}
	else if(len==5 && strcmp(EventMessage, "WATER")==0)
	{
		m_cDynamicState |= UNDERWATER ;

		if(!m_bSEWater)
		{
			m_bSEWater = true ;
			g_MusicManager->PlayMusic(m_pSEWater, 2) ;
		}

		if(!m_bRespiration)
			m_bDeath = true ;
	}
	else if(len==11 && strcmp(EventMessage, "RESPIRATION")==0)
	{
		m_bRespiration = true ;
	}
	else if(len==7 && strcmp(EventMessage, "ARRIVAL")==0)
	{
		g_StageProgress->StageClear() ;
	}
}

void CHero::EventClear()
{
	m_bRespiration = false ;

	m_cDynamicState &= ~UNDERWATER ;
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
	if(m_bDeath)
		return ;

	float fTime = g_D3dDevice->GetMoveTime() ;
	float fSpeed = m_fVecSpeed * fTime ;

	m_vForce.x = 0.0f ;
	m_vForce.y = 0.0f ;

	if(m_bReleaseAbsorb && !m_bAir && g_Keyboard->IsButtonDown(DIK_Z))
	{
		const State SkilState = (State)(m_State % RIGHT) ;
		if(SkilState!=LEFT_ABSORB && SkilState!=LEFT_RELEASE)
			g_MusicManager->PlayMusic(m_pSESkill, 1) ;

		m_State = (State)((m_State / RIGHT) * RIGHT + LEFT_RELEASE) ;

		// 현재 선택되어있는 친구가 방출되어 있지 않다면
		int index = m_pFC_UI->GetSelectedIndex() ;
		CFriends *pFriend = g_Friends_List->GetFriend(index) ;
		if(pFriend!=NULL && !pFriend->GetRelease())
		{
			// 캐릭터가 바라보는 방향의 타일 좌표를 구한다
			float fX ;
			int tileX, tileY ;
			if(m_State==LEFT_RELEASE)
			{
				fX = m_fX + (m_BoundingBox.left + 32.0f) ;
				tileX = (int)(fX / 64.0f) - 1 ;
			}
			else if(m_State==RIGHT_RELEASE)
			{
				fX = m_fX + (m_BoundingBox.right + 32.0f - 1.0f) ;
				tileX = (int)(fX / 64.0f) + 1 ;
			}
			tileY = (int)((m_fY + 32.0f) / 64.0f) ;

			// 해당 좌표에 친구가 없을경우, 현재 선택된 친구를 방출
			// 해당 좌표에 친구/타일 이 없을경우, 현재 선택된 친구를 방출
			if( g_Friends_List->GetFriend(tileX, tileY)==NULL &&
				g_MapTiles_List->GetTile(tileX, tileY)==NULL )
			{
				fX = (float)(tileX * 64) ;
				pFriend->SetPosition(fX, m_fY) ;

				pFriend->Release() ;
			}
		}
	}
	else if(m_bReleaseAbsorb && !m_bAir && g_Keyboard->IsButtonDown(DIK_X))
	{
		const State SkilState = (State)(m_State % RIGHT) ;
		if(SkilState!=LEFT_ABSORB && SkilState!=LEFT_RELEASE)
			g_MusicManager->PlayMusic(m_pSESkill, 1) ;

		m_State = (State)((m_State / RIGHT) * RIGHT + LEFT_ABSORB) ;

		// 캐릭터가 바라보는 방향의 타일 좌표를 구한다
		float fX ;
		int tileX, tileY ;
		if(m_State==LEFT_ABSORB)
		{
			fX = m_fX + (m_BoundingBox.left + 32.0f) ;
			tileX = (int)(fX / 64.0f) - 1 ;
		}
		else if(m_State==RIGHT_ABSORB)
		{
			fX = m_fX + (m_BoundingBox.right + 32.0f - 1.0f) ;
			tileX = (int)(fX / 64.0f) + 1 ;
		}
		tileY = (int)((m_fY + 32.0f) / 64.0f) ;

		// 해당 좌표에 있는 친구를 흡수한다
		CFriends *pFriends = g_Friends_List->GetFriend(tileX, tileY) ;
		if(pFriends!=NULL && g_MapTiles_List->GetTile(tileX, tileY)==NULL)
		{
			pFriends->Absorb() ;
		}
	}
	else
	{
		const State SkilState = (State)(m_State % RIGHT) ;
		if(SkilState==LEFT_ABSORB || SkilState==LEFT_RELEASE)
			g_MusicManager->StopMusic(1) ;

		m_State = (State)((m_State / RIGHT) * RIGHT + LEFT) ;

		if(g_Keyboard->IsButtonDown(DIK_LEFT))
			m_vForce.x -= fSpeed ;
		if(g_Keyboard->IsButtonDown(DIK_RIGHT))
			m_vForce.x += fSpeed ;

		if((!m_bAir || m_bMultipleJump) && !m_bJump && g_Keyboard->IsButtonDown(DIK_UP))
		{
			m_fVecAcc = m_fVecJump * fTime ;

			m_bJump = true ;

			g_MusicManager->PlayMusic(m_pSEJump, 2) ;
		}
	}

	m_fX += m_vForce.x ;
}

void CHero::Death()
{
	if(m_Dying==SINK)
	{
		if(m_fTime>=1.0f)
		{
			m_fTime = 0.0f ;
			m_Dying = BUBBLE ;
			
			m_pEffect_Bubble->SetDirection() ;
			m_pSprite->SetAlpha(150) ;
			return ;
		}
	}
	else if(m_Dying==BUBBLE)
	{
		m_pEffect_Bubble->Update() ;

		if(m_fTime>=0.8f)
		{
			m_fTime = 0.0f ;
			m_Dying = FADE_AWAY ;
			return ;
		}
	}
	else if(m_Dying==FADE_AWAY)
	{
		int Alpha = 150 - ((int)(m_fTime / 0.1f) * 25) ;
		m_pSprite->SetAlpha(Alpha) ;

		if(m_fTime>=0.4f)
		{
			m_fTime = 0.0f ;
			m_Dying = SOUL_OUT ;
			
			m_pEffect_Soul->SetDirection() ;
			m_pEffect_Soul->SetPosition(m_fX, m_fY) ;
			SetGravity(false) ;
			return ;
		}
	}
	else if(m_Dying==SOUL_OUT)
	{
		int Alpha = 100 + ((int)(m_fTime / 0.1f) * 25) ;
		m_pEffect_Soul->SetAlpha(Alpha) ;

		if(m_fTime>=0.4f)
		{
			m_fTime = 0.0f ;
			m_Dying = SOUL ;
		}
	}
	else if(m_Dying==SOUL)
	{
		m_pEffect_Soul->Update() ;

		if(m_fTime>=3.0f)
		{
			g_StageProgress->StageOver() ;
			return ;
		}
	}

	m_fTime += g_D3dDevice->GetTime() ;
}

void CHero::Animation()
{
	// Direction
	if(m_bAir)
	{
		if(m_vForce.x<0)
			m_State = LEFT_JUMP ;
		else if(m_vForce.x>0)
			m_State = RIGHT_JUMP ;
		else
		{
			m_State = (State)((m_State / RIGHT) * RIGHT + LEFT_JUMP) ;
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
	}

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
	m_fAnimationTime += g_D3dDevice->GetTime() ;

	if(m_fAnimationTime>=0.2f || (m_State!=m_prevState))
	{
		if(m_State!=m_prevState)
		{
			m_fAnimationTime = 0.0f ;
			m_nNowFrame = 0 ;
		}

		int Frame = (int)(m_fAnimationTime / 0.2f) ;
		m_fAnimationTime -= Frame * 0.2f ;
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