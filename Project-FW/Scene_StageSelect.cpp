#include "Scene_StageSelect.h"
#include "Scene_Gravity.h"
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

SceneStageSelect::SceneStageSelect() : m_pBackground(NULL),
									   m_pBackground_Brick(NULL), m_pMenuFrame(NULL),
									   m_pPlayer(NULL), m_pGoal(NULL),
									   m_pPrev(NULL), m_pNext(NULL), m_pBack(NULL),
									   m_pChapterNumber(NULL), m_pStageNumber(NULL), m_pStageName(NULL),
									   m_bPressPrev(false), m_bPressNext(false),
									   m_fBackgroundX(0.0f)
{
	for(int i=0; i<5; i++)
		m_pProgress[i] = NULL ;
}
SceneStageSelect::~SceneStageSelect()
{
	if(m_pBackground!=NULL)
		delete m_pBackground ;

	if(m_pBackground_Brick!=NULL)
		delete m_pBackground_Brick ;
	if(m_pMenuFrame!=NULL)
		delete m_pMenuFrame ;

	for(int i=0; i<5; i++)
	{
		if(m_pProgress[i]!=NULL)
			delete m_pProgress[i] ;
	}
	if(m_pPlayer!=NULL)
		delete m_pPlayer ;
	if(m_pGoal!=NULL)
		delete m_pGoal ;

	if(m_pPrev!=NULL)
		delete m_pPrev ;
	if(m_pNext!=NULL)
		delete m_pNext ;
	if(m_pBack!=NULL)
		delete m_pBack ;

	if(m_pChapterNumber!=NULL)
		delete m_pChapterNumber ;
	if(m_pStageNumber!=NULL)
		delete m_pStageNumber ;
	if(m_pStageName!=NULL)
		delete m_pStageName ;

	FreeStageName() ;
}

Scene* SceneStageSelect::scene()
{
	Scene *scene = new SceneStageSelect ;

	return scene ;
}

void SceneStageSelect::Init()
{
	float fWinWidth = (float)g_D3dDevice->GetWinWidth() ;
	float fWinHeight = (float)g_D3dDevice->GetWinHeight() ;
	
	g_CameraManager->AllCameraClear() ;
	g_CameraManager->AddCamera(new CCamera()) ;

	m_pBackground = new CScrollBackground ;
	m_pBackground->Init(1024.0f, 768.0f, "Resource/Image/StageSelect/Background.png") ;
	m_pBackground->SetTextureUV(0.0f, 0.0f, 1024.0f, 768.0f) ;
	m_pBackground->SetPosition(fWinWidth / 2.0f, fWinHeight / 2.0f) ;
	m_pBackground->SetScrollSpeed(1.0f, 0.0f) ;

	m_pBackground_Brick = new CSprite ;
	m_pBackground_Brick->Init("Resource/Image/StageSelect/Background_Brick.png") ;
	m_pBackground_Brick->SetPosition(fWinWidth / 2.0f, fWinHeight / 2.0f) ;

	m_pMenuFrame = new CSprite ;
	m_pMenuFrame->Init("Resource/Image/StageSelect/MenuFrame.png") ;
	m_pMenuFrame->SetPosition(fWinWidth / 2.0f, fWinHeight / 2.0f) ;

	const int nChapterProgress = g_StageProgress->GetChapterProgress() ;

	for(int i=0; i<5; i++)
	{
		m_pProgress[i] = new CSprite ;
		m_pProgress[i]->Init(28.0f, 28.0f, "Resource/Image/StageSelect/Progress.png") ;
		m_pProgress[i]->SetPosition(570.0f + (i * 103.0f), fWinHeight - 92.0f) ;
		if(i<nChapterProgress)
			m_pProgress[i]->SetTextureUV(0.0f, 0.0f, 28.0f, 28.0f) ;
		else
			m_pProgress[i]->SetTextureUV(28.0f, 0.0f, 56.0f, 28.0f) ;
	}

	m_pPlayer = new CSprite ;
	m_pPlayer->Init("Resource/Image/StageSelect/Player.png") ;
	m_pPlayer->SetPosition(570.0f + ((nChapterProgress-1) * 103.0f), fWinHeight - 52.0f) ;
	
	m_pGoal = new CSprite ;
	m_pGoal->Init("Resource/Image/StageSelect/Goal.png") ;
	m_pGoal->SetPosition(978.0f, fWinHeight - 48.0f) ;

	m_pPrev = new CSprite ;
	m_pPrev->Init(70.0f, 80.0f, "Resource/Image/StageSelect/Prev.png") ;
	m_pPrev->SetTextureUV(0.0f, 0.0f, 70.0f, 80.0f) ;
	m_pPrev->SetPosition(280.0f, fWinHeight - 723.0f) ;

	m_pNext = new CSprite ;
	m_pNext->Init(70.0f, 80.0f, "Resource/Image/StageSelect/Next.png") ;
	m_pNext->SetTextureUV(0.0f, 0.0f, 70.0f, 80.0f) ;
	m_pNext->SetPosition(744.0f, fWinHeight - 723.0f) ;

	m_pBack = new CSprite ;
	m_pBack->Init(96.0f, 96.0f, "Resource/Image/StageSelect/Back.png") ;
	m_pBack->SetTextureUV(0.0f, 0.0f, 96.0f, 96.0f) ;
	m_pBack->SetPosition(60.0f, fWinHeight - 60.0f) ;

	const int nChapter = g_StageProgress->GetSelectChapter() ;
	const int nStage = g_StageProgress->GetSelectStage() ;

	m_pChapterNumber = new CSprite ;
	m_pChapterNumber->Init(195.0f, 40.0f, "Resource/Image/StageSelect/ChapterNumber.png") ;
	m_pChapterNumber->SetTextureUV(0.0f, 0.0f, 195.0f, 40.0f) ;
	m_pChapterNumber->SetTextureUV(0.0f, ((nChapter-1) * 40.0f), 195.0f, (nChapter * 40.0f)) ;
	m_pChapterNumber->SetPosition(307.0f, fWinHeight - 60.0f) ;

	m_pStageNumber = new CSprite ;
	m_pStageNumber->Init(225.0f, 40.0f, "Resource/Image/StageSelect/StageNumber.png") ;
	m_pStageNumber->SetTextureUV(0.0f, 0.0f, 225.0f, 40.0f) ;
	m_pStageNumber->SetTextureUV(0.0f, ((nStage-1) * 40.0f), 225.0f, (nStage * 40.0f)) ;
	m_pStageNumber->SetPosition(fWinWidth / 2.0f, fWinHeight - 723.0f) ;

	m_pStageName = new CSprite ;
	m_pStageName->Init(256.0f, 30.0f, "Resource/Image/StageSelect/Chapter1_StageName.png") ;
	m_pStageName->SetTextureUV(0.0f, ((nStage-1) * 30.0f), 256.0f, (nStage * 30.0f)) ;
	m_pStageName->SetPosition(395.0f, fWinHeight - 242.0f) ;

	AllocateStageName() ;
}

void SceneStageSelect::Destroy()
{
}

void SceneStageSelect::Update(float dt)
{
	g_Keyboard->Update() ;
	g_Mouse->Update() ;
	g_Joystick->Update() ;
	g_MusicManager->Loop() ;

	m_pBackground->Scroll() ;
	StageSelect() ;

	if(g_Keyboard->IsPressDown(DIK_SPACE) || g_Keyboard->IsPressDown(DIK_Z))
	{
		g_SceneManager->ChangeScene(SceneGravity::scene()) ;
		return ;
	}
	else if(g_Keyboard->IsPressDown(DIK_ESCAPE) || g_Keyboard->IsPressDown(DIK_X))
	{
		m_pBack->SetTextureUV(96.0f, 0.0f, 192.0f, 96.0f) ;
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
	m_pMenuFrame->Render() ;

	for(int i=0; i<5; i++)
		m_pProgress[i]->Render() ;
	m_pGoal->Render() ;
	m_pPlayer->Render() ;

	m_pPrev->Render() ;
	m_pNext->Render() ;
	m_pBack->Render() ;

	m_pChapterNumber->Render() ;
	m_pStageNumber->Render() ;
	m_pStageName->Render() ;
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
	FreeStageName() ;

	const int nChapter = g_StageProgress->GetSelectChapter() ;
	char filepath[1024] ;
	sprintf_s(filepath, "Resource/Image/StageSelect/Chapter%d_StageName.png", nChapter) ;

	m_pStageName->SetTexture(filepath) ;
}

void SceneStageSelect::FreeStageName()
{
	if(m_StagePreview_List.empty())
		return ;

	const int num = m_StagePreview_List.size() ;

	for(int i=0; i<num; i++)
		delete m_StagePreview_List[i] ;

	m_StagePreview_List.clear() ;
}