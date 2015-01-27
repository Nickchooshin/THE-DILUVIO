#include "Scene_StageSelect.h"
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

#include "LoadManager.h"
#include "StageProgress.h"
#include "ScrollBackground.h"

SceneStageSelect::SceneStageSelect() : m_fWinWidth(g_D3dDevice->GetWinWidth()), m_fWinHeight(g_D3dDevice->GetWinHeight()),
									   m_pBackground(NULL),
									   m_pBackground_Brick(NULL), m_pStageFrame(NULL), m_pStageNameFrame(NULL),
									   m_pPlayer(NULL), m_pGoal(NULL), m_pTile(NULL),
									   m_pPrev(NULL), m_pNext(NULL),
									   m_pChapterNumber(NULL), m_pStageNumber(NULL), m_pStageName(NULL),
									   m_pStagePreview_List(NULL),
									   m_bPressPrev(false), m_bPressNext(false),
									   m_fBackgroundX(0.0f),
									   m_pBGM(NULL)
{
	for(int i=0; i<5; i++)
		m_pProgress[i] = NULL ;

	m_pStagePreview_List = new CSprite*[9] ;
	for(int i=0; i<9; i++)
		m_pStagePreview_List[i] = NULL ;
}
SceneStageSelect::~SceneStageSelect()
{
	if(m_pBackground!=NULL)
		delete m_pBackground ;

	if(m_pBackground_Brick!=NULL)
		delete m_pBackground_Brick ;
	if(m_pStageFrame!=NULL)
		delete m_pStageFrame ;
	if(m_pStageNameFrame!=NULL)
		delete m_pStageNameFrame ;

	for(int i=0; i<5; i++)
	{
		if(m_pProgress[i]!=NULL)
			delete m_pProgress[i] ;
	}
	if(m_pPlayer!=NULL)
		delete m_pPlayer ;
	if(m_pGoal!=NULL)
		delete m_pGoal ;
	if(m_pTile!=NULL)
		delete m_pTile ;

	if(m_pPrev!=NULL)
		delete m_pPrev ;
	if(m_pNext!=NULL)
		delete m_pNext ;

	if(m_pChapterNumber!=NULL)
		delete m_pChapterNumber ;
	if(m_pStageNumber!=NULL)
		delete m_pStageNumber ;
	if(m_pStageName!=NULL)
		delete m_pStageName ;

	FreeStagePreview() ;
	delete[] m_pStagePreview_List ;
}

Scene* SceneStageSelect::scene()
{
	Scene *scene = new SceneStageSelect ;

	return scene ;
}

void SceneStageSelect::Init()
{
	g_CameraManager->AllCameraClear() ;
	g_CameraManager->AddCamera(new CCamera()) ;

	m_pBackground = new CScrollBackground ;
	m_pBackground->Init(1024.0f, 768.0f, "Resource/Image/StageSelect/Background.png") ;
	m_pBackground->SetTextureUV(0.0f, 0.0f, 1024.0f, 768.0f) ;
	m_pBackground->SetPosition(m_fWinWidth / 2.0f, m_fWinHeight / 2.0f) ;
	m_pBackground->SetScrollSpeed(1.0f, 0.0f) ;

	m_pBackground_Brick = new CSprite ;
	m_pBackground_Brick->Init("Resource/Image/StageSelect/Background_Brick.png") ;
	m_pBackground_Brick->SetPosition(m_fWinWidth / 2.0f, m_fWinHeight / 2.0f) ;

	m_pStageFrame = new CSprite ;
	m_pStageFrame->Init("Resource/Image/StageSelect/StageFrame.png") ;
	m_pStageFrame->SetPosition(m_fWinWidth / 2.0f, m_fWinHeight - 300.0f) ;

	m_pStageNameFrame = new CSprite ;
	m_pStageNameFrame->Init("Resource/Image/StageSelect/StageNameFrame.png") ;
	m_pStageNameFrame->SetPosition(425.0f, m_fWinHeight - 50.0f) ;

	const int nChapterProgress = g_StageProgress->GetChapterProgress() ;

	for(int i=0; i<5; i++)
	{
		m_pProgress[i] = new CSprite ;
		m_pProgress[i]->Init(64.0f, 64.0f, "Resource/Image/StageSelect/Flag.png") ;
		m_pProgress[i]->SetPosition(32.0f + (i * 240.0f), m_fWinHeight - 672.0f + ((i/4) * 43.0f)) ;
		if(i<nChapterProgress)
			m_pProgress[i]->SetTextureUV(0.0f, 64.0f, 64.0f, 128.0f) ;
		else
			m_pProgress[i]->SetTextureUV(0.0f, 0.0f, 64.0f, 64.0f) ;
	}

	m_pPlayer = new CSprite ;
	m_pPlayer->Init(64.0f, 64.0f, "Resource/Image/Char/Main_character.png") ;
	m_pPlayer->SetPosition(32.0f + ((nChapterProgress-1) * 240.0f), m_fWinHeight - 672.0f) ;
	m_pPlayer->SetTextureUV(0.0f, 64.0f, 64.0f, 128.0f) ;
	
	m_pGoal = new CSprite ;
	m_pGoal->Init("Resource/Image/StageSelect/Castle.png") ;
	m_pGoal->SetPosition(992.0f, m_fWinHeight - 672.0f) ;

	m_pTile = new CSprite ;
	m_pTile->Init(64.0f, 64.0f, "Resource/Image/Terrain/Tiles.png") ;
	m_pTile->SetTextureUV(128.0f, 0.0f, 192.0f, 64.0f) ;

	m_pPrev = new CSprite ;
	m_pPrev->Init(70.0f, 80.0f, "Resource/Image/StageSelect/Prev.png") ;
	m_pPrev->SetTextureUV(0.0f, 0.0f, 70.0f, 80.0f) ;
	m_pPrev->SetPosition(262.0f, m_fWinHeight - 580.0f) ;

	m_pNext = new CSprite ;
	m_pNext->Init(70.0f, 80.0f, "Resource/Image/StageSelect/Next.png") ;
	m_pNext->SetTextureUV(0.0f, 0.0f, 70.0f, 80.0f) ;
	m_pNext->SetPosition(762.0f, m_fWinHeight - 580.0f) ;

	const int nChapter = g_StageProgress->GetSelectChapter() ;
	const int nStage = g_StageProgress->GetSelectStage() ;

	m_pChapterNumber = new CSprite ;
	m_pChapterNumber->Init(195.0f, 40.0f, "Resource/Image/StageSelect/ChapterNumber.png") ;
	m_pChapterNumber->SetTextureUV(0.0f, 0.0f, 195.0f, 40.0f) ;
	m_pChapterNumber->SetTextureUV(0.0f, ((nChapter-1) * 40.0f), 195.0f, (nChapter * 40.0f)) ;
	m_pChapterNumber->SetPosition(450.0f, m_fWinHeight - 560.0f) ;

	m_pStageNumber = new CSprite ;
	m_pStageNumber->Init(225.0f, 40.0f, "Resource/Image/StageSelect/StageNumber.png") ;
	m_pStageNumber->SetTextureUV(0.0f, 0.0f, 225.0f, 40.0f) ;
	m_pStageNumber->SetTextureUV(0.0f, ((nStage-1) * 40.0f), 225.0f, (nStage * 40.0f)) ;
	m_pStageNumber->SetPosition(580.0f, m_fWinHeight - 600.0f) ;

	m_pStageName = new CSprite ;
	m_pStageName->Init(256.0f, 30.0f, "Resource/Image/StageSelect/Chapter1_StageName.png") ;
	m_pStageName->SetPosition(395.0f, m_fWinHeight - 50.0f) ;
	AllocateStageName() ;
	m_pStageName->SetTextureUV(0.0f, ((nStage-1) * 30.0f), 256.0f, (nStage * 30.0f)) ;

	m_pBGM = g_MusicManager->LoadMusic("Resource/Sound/BGM_StageSelect.mp3", true, true) ;
	g_MusicManager->PlayMusic(m_pBGM) ;
}

void SceneStageSelect::Destroy()
{
	g_MusicManager->StopMusic() ;
}

void SceneStageSelect::Update(float dt)
{
	g_Keyboard->Update() ;
	g_Mouse->Update() ;
	g_Joystick->Update() ;
	g_MusicManager->Loop() ;

	m_pBackground->Scroll() ;
	StageSelect() ;

	if(g_Keyboard->IsPressDown(DIK_RETURN) || g_Keyboard->IsPressDown(DIK_SPACE) || g_Keyboard->IsPressDown(DIK_Z))
	{
		g_SceneManager->ChangeScene(SceneGame::scene()) ;
		return ;
	}
	else if(g_Keyboard->IsPressDown(DIK_ESCAPE) || g_Keyboard->IsPressDown(DIK_X))
	{
		g_SceneManager->ChangeScene(SceneTitle::scene()) ;
		return ;
	}
}

void SceneStageSelect::Render()
{
	g_CameraManager->CameraRun() ;

	if(g_StageProgress->GetSelectChapter()<5)
		m_pBackground->Render() ;
	else
		m_pBackground_Brick->Render() ;
	m_pStageNameFrame->Render() ;
	
	for(int i=0; i<16; i++)
	{
		m_pTile->SetPosition(32.0f + (i * 64.0f), m_fWinHeight - 736.0f) ;
		m_pTile->Render() ;
	}
	for(int i=0; i<5; i++)
		m_pProgress[i]->Render() ;
	m_pGoal->Render() ;
	m_pPlayer->Render() ;

	m_pPrev->Render() ;
	m_pNext->Render() ;

	m_pChapterNumber->Render() ;
	m_pStageNumber->Render() ;
	m_pStageName->Render() ;
	const int nStage = g_StageProgress->GetSelectStage() - 1 ;
	m_pStagePreview_List[nStage]->Render() ;
	m_pStageFrame->Render() ;
}

void SceneStageSelect::StageSelect()
{
	const int prevChapter = g_StageProgress->GetSelectChapter() ;
	const int prevStage = g_StageProgress->GetSelectStage() ;
	int nowChapter, nowStage ;

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

		nowChapter = g_StageProgress->GetSelectChapter() ;
		if(nowChapter!=prevChapter)
		{
			m_pChapterNumber->SetTextureUV(0.0f, ((nowChapter-1) * 40.0f), 195.0f, (nowChapter * 40.0f)) ;

			AllocateStageName() ;
		}
		
		m_pStageName->SetTextureUV(0.0f, ((nowStage-1) * 30.0f), 256.0f, (nowStage * 30.0f)) ;
	}
}

void SceneStageSelect::AllocateStageName()
{
	FreeStagePreview() ;

	const int nChapter = g_StageProgress->GetSelectChapter() ;
	const int nMaxStage = g_StageProgress->nChapterMaxStage[nChapter-1] ;
	char filepath[1024] ;

	sprintf_s(filepath, "Resource/Image/StageSelect/Chapter%d_StageName.png", nChapter) ;
	m_pStageName->SetTexture(filepath) ;

	for(int i=0; i<nMaxStage; i++)
	{
		sprintf_s(filepath, "Resource/Image/StageSelect/Preview/Chapter%d_%d.png", nChapter, i+1) ;
		m_pStagePreview_List[i] = new CSprite ;
		m_pStagePreview_List[i]->Init(filepath) ;
		m_pStagePreview_List[i]->SetPosition(m_fWinWidth / 2.0f, m_fWinHeight - 300.0f) ;
	}
}

void SceneStageSelect::FreeStagePreview()
{
	for(int i=0; i<9; i++)
	{
		if(m_pStagePreview_List[i]!=NULL)
		{
			delete m_pStagePreview_List[i] ;
			m_pStagePreview_List[i] = NULL ;
		}
	}
}