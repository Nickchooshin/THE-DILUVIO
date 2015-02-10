#include "Scene_ExtraStageSelect.h"
#include "Scene_Game.h"
#include "Scene_Title.h"

#include "Keyboard.h"
#include "Mouse.h"
#include "Joystick.h"

#include "Sprite.h"
#include "UISprite.h"
#include "CameraManager.h"
#include "MusicManager.h"
#include "SceneManager.h"

#include "D3dDevice.h"

#include "StageProgress.h"
#include "Hero.h"

SceneExtraStageSelect::SceneExtraStageSelect() : m_fWinWidth((float)g_D3dDevice->GetWinWidth()), m_fWinHeight((float)g_D3dDevice->GetWinHeight()),
												 m_pBackground(NULL),
												 m_pStageFrame(NULL), m_pStageNameFrame(NULL),
												 m_pPlayer(NULL), m_pCastle(NULL), m_pTile(NULL),
												 m_pPrev(NULL), m_pNext(NULL),
												 m_pStageNumber(NULL), m_pStageName(NULL),
												 m_pStagePreview_List(NULL),
												 m_bPressPrev(false), m_bPressNext(false),
												 m_fPlayerAnimationTime(0.0f),
												 m_nPlayerFrame(0),
												 m_pBGM(NULL)
{
	m_pStagePreview_List = new CSprite*[9] ;
	for(int i=0; i<9; i++)
		m_pStagePreview_List[i] = NULL ;
}
SceneExtraStageSelect::~SceneExtraStageSelect()
{
	if(m_pBackground!=NULL)
		delete m_pBackground ;

	if(m_pStageFrame!=NULL)
		delete m_pStageFrame ;
	if(m_pStageNameFrame!=NULL)
		delete m_pStageNameFrame ;

	if(m_pPlayer!=NULL)
		delete m_pPlayer ;
	if(m_pCastle!=NULL)
		delete m_pCastle ;
	if(m_pTile!=NULL)
		delete m_pTile ;

	if(m_pPrev!=NULL)
		delete m_pPrev ;
	if(m_pNext!=NULL)
		delete m_pNext ;

	if(m_pStageNumber!=NULL)
		delete m_pStageNumber ;
	if(m_pStageName!=NULL)
		delete m_pStageName ;

	for(int i=0; i<9; i++)
		delete m_pStagePreview_List[i] ;
	delete[] m_pStagePreview_List ;
}

Scene* SceneExtraStageSelect::scene()
{
	Scene *scene = new SceneExtraStageSelect ;

	return scene ;
}

void SceneExtraStageSelect::Init()
{
	g_CameraManager->AllCameraClear() ;
	g_CameraManager->AddCamera(new CCamera()) ;

	g_StageProgress->SetMapType(g_StageProgress->EXTRA) ;

	m_pBackground = new CSprite ;
	m_pBackground->Init("Resource/Image/StageSelect/Background_Brick.png") ;
	m_pBackground->SetPosition(m_fWinWidth / 2.0f, m_fWinHeight / 2.0f) ;

	m_pStageFrame = new CSprite ;
	m_pStageFrame->Init("Resource/Image/StageSelect/StageFrame.png") ;
	m_pStageFrame->SetPosition(m_fWinWidth / 2.0f, m_fWinHeight - 300.0f) ;

	m_pStageNameFrame = new CSprite ;
	m_pStageNameFrame->Init("Resource/Image/StageSelect/StageNameFrame.png") ;
	m_pStageNameFrame->SetPosition(425.0f, m_fWinHeight - 50.0f) ;

	m_pPlayer = new CSprite ;
	m_pPlayer->Init(64.0f, 64.0f, "Resource/Image/Char/Main_character.png") ;
	m_pPlayer->SetPosition(32.0f + ((g_StageProgress->GetSelectStage()-1) * 120.0f), m_fWinHeight - 672.0f) ;
	m_pPlayer->SetTextureUV(64.0f, 64.0f, 128.0f, 128.0f) ;
	if(CHero::m_bExVersion)
		m_pPlayer->SetTexture("Resource/Image/Char/Main_character_Ex.png") ;

	m_pCastle = new CSprite ;
	m_pCastle->Init("Resource/Image/StageSelect/Castle.png") ;
	m_pCastle->SetPosition(992.0f, m_fWinHeight - 672.0f) ;

	m_pTile = new CSprite ;
	m_pTile->Init(64.0f, 64.0f, "Resource/Image/Terrain/Tiles.png") ;
	m_pTile->SetTextureUV(0.0f, 0.0f, 64.0f, 64.0f) ;

	m_pPrev = new CSprite ;
	m_pPrev->Init(70.0f, 80.0f, "Resource/Image/StageSelect/Prev.png") ;
	m_pPrev->SetTextureUV(0.0f, 0.0f, 70.0f, 80.0f) ;
	m_pPrev->SetPosition(262.0f, m_fWinHeight - 580.0f) ;

	m_pNext = new CSprite ;
	m_pNext->Init(70.0f, 80.0f, "Resource/Image/StageSelect/Next.png") ;
	m_pNext->SetTextureUV(0.0f, 0.0f, 70.0f, 80.0f) ;
	m_pNext->SetPosition(762.0f, m_fWinHeight - 580.0f) ;

	const int nStage = g_StageProgress->GetSelectStage() ;

	m_pStageNumber = new CSprite ;
	m_pStageNumber->Init(225.0f, 40.0f, "Resource/Image/StageSelect/StageNumber.png") ;
	m_pStageNumber->SetTextureUV(0.0f, 0.0f, 225.0f, 40.0f) ;
	m_pStageNumber->SetTextureUV(0.0f, ((nStage-1) * 40.0f), 225.0f, (nStage * 40.0f)) ;
	m_pStageNumber->SetPosition(m_fWinWidth / 2.0f, m_fWinHeight - 580.0f) ;

	m_pStageName = new CSprite ;
	m_pStageName->Init(256.0f, 30.0f, "Resource/Image/Extra/Extra_StageName.png") ;
	m_pStageName->SetPosition(395.0f, m_fWinHeight - 50.0f) ;
	m_pStageName->SetTextureUV(0.0f, ((nStage-1) * 30.0f), 256.0f, (nStage * 30.0f)) ;

	for(int i=0; i<9; i++)
	{
		char filepath[100] ;
		sprintf_s(filepath, "Resource/Image/Extra/Preview/EXTRA%03d.png", i+1) ;

		m_pStagePreview_List[i] = new CSprite ;
		m_pStagePreview_List[i]->Init(filepath) ;
		m_pStagePreview_List[i]->SetPosition(m_fWinWidth / 2.0f, m_fWinHeight - 300.0f) ;
	}

	m_pBGM = g_MusicManager->LoadMusic("Resource/Sound/BGM_StageSelect.mp3", true, true) ;
	g_MusicManager->PlayMusic(m_pBGM) ;
}

void SceneExtraStageSelect::Destroy()
{
	g_MusicManager->StopMusic() ;
}

void SceneExtraStageSelect::Update(float dt)
{
	g_Keyboard->Update() ;
	g_Mouse->Update() ;
	g_Joystick->Update() ;
	g_MusicManager->Loop() ;

	StageSelect() ;
	
	PlayerAnimation() ;
	m_pPlayer->SetPositionX(32.0f + ((g_StageProgress->GetSelectStage()-1) * 120.0f)) ;

	if(g_Keyboard->IsPressDown(DIK_RETURN) || g_Keyboard->IsPressDown(DIK_SPACE))
	{
		g_SceneManager->ChangeScene(SceneGame::scene()) ;
		return ;
	}
	else if(g_Keyboard->IsPressDown(DIK_ESCAPE))
	{
		g_SceneManager->ChangeScene(SceneTitle::scene()) ;
		return ;
	}
}

void SceneExtraStageSelect::Render()
{
	g_CameraManager->CameraRun() ;

	m_pBackground->Render() ;
	m_pStageNameFrame->Render() ;
	
	for(int i=0; i<16; i++)
	{
		m_pTile->SetPosition(32.0f + (i * 64.0f), m_fWinHeight - 736.0f) ;
		m_pTile->Render() ;
	}
	for(int i=0; i<9; i++)
	{
		m_pCastle->SetPosition(32.0f + (i * 120.0f), m_fWinHeight - 672.0f) ;
		m_pCastle->Render() ;
	}
	m_pPlayer->Render() ;

	m_pPrev->Render() ;
	m_pNext->Render() ;

	m_pStageNumber->Render() ;
	m_pStageName->Render() ;
	const int nStage = g_StageProgress->GetSelectStage() - 1 ;
	m_pStagePreview_List[nStage]->Render() ;
	m_pStageFrame->Render() ;
}

void SceneExtraStageSelect::StageSelect()
{
	const int prevStage = g_StageProgress->GetSelectStage() ;
	int nowStage ;

	if(g_Keyboard->IsPressDown(DIK_LEFT))
		m_bPressPrev = g_StageProgress->PrevStage() ;
	if(g_Keyboard->IsPressDown(DIK_RIGHT))
		m_bPressNext = g_StageProgress->NextStage() ;

	if(m_bPressPrev)
	{
		if(g_Keyboard->IsButtonDown(DIK_LEFT))
		{
			m_pPrev->SetTextureUV(70.0f, 0.0f, 140.0f, 80.0f) ;
		}
		else
		{
			m_pPrev->SetTextureUV(0.0f, 0.0f, 70.0f, 80.0f) ;
			m_bPressPrev = false ;
		}
	}
	if(m_bPressNext)
	{
		if(g_Keyboard->IsButtonDown(DIK_RIGHT))
		{
			m_pNext->SetTextureUV(70.0f, 0.0f, 140.0f, 80.0f) ;
		}
		else
		{
			m_pNext->SetTextureUV(0.0f, 0.0f, 70.0f, 80.0f) ;
			m_bPressNext = false ;
		}
	}

	nowStage = g_StageProgress->GetSelectStage() ;
	if(nowStage!=prevStage)
	{
		m_pStageNumber->SetTextureUV(0.0f, ((nowStage-1) * 40.0f), 225.0f, (nowStage * 40.0f)) ;
		m_pStageName->SetTextureUV(0.0f, ((nowStage-1) * 30.0f), 256.0f, (nowStage * 30.0f)) ;
	}
}

void SceneExtraStageSelect::PlayerAnimation()
{
	if(m_fPlayerAnimationTime>=0.2f)
	{
		int Frame = (int)(m_fPlayerAnimationTime / 0.2f) ;
		m_fPlayerAnimationTime -= Frame * 0.2f ;
		Frame %= 3 ;
		m_nPlayerFrame += Frame ;
		m_nPlayerFrame %= 3 ;
		
		float left, top, right, bottom ;
		left = (float)((m_nPlayerFrame+1) * 64) ;
		top = 64.0f ;
		right = (float)((m_nPlayerFrame+2) * 64) ;
		bottom = 128.0f ;

		m_pPlayer->SetTextureUV(left, top, right, bottom) ;
	}

	m_fPlayerAnimationTime += g_D3dDevice->GetTime() ;
}