#include "Scene_Game.h"
#include "Scene_StageSelect.h"
#include "Scene_Credit.h"

#include "Keyboard.h"
#include "Mouse.h"
#include "Joystick.h"

#include "Sprite.h"
#include "UISprite.h"
#include "CameraManager.h"
#include "MusicManager.h"
#include "SceneManager.h"

#include "D3dDevice.h"

#include "Hero.h"

#include "MapTiles_List.h"
#include "Friends_List.h"
#include "DynamicObjects_List.h"
#include "Effect_List.h"
#include "MapBackground.h"

#include "StageProgress.h"

#include "CollisionManager.h"

SceneGame::SceneGame() : m_pHero(NULL),
						 m_pMapBackground(NULL),
						 m_pTutorial(NULL),
						 m_pEndMenu(NULL),
						 m_fTime(0.0f),
						 m_bTutorial(false),
						 m_bMenu(false),
						 m_nSelectMenuNum(0),
						 m_GameEndMenuState(NONE),
						 m_pBGM(NULL)
{
	int i ;

	for(i=0; i<3; i++)
		m_pMenuButton[i] = NULL ;
	for(i=0; i<2; i++)
		m_pEndMenuButton[i] = NULL ;
}
SceneGame::~SceneGame()
{
	int i ;

	if(m_pHero!=NULL)
		delete m_pHero ;
	if(m_pMapBackground!=NULL)
		delete m_pMapBackground ;

	g_DynamicObjects_List->Clear() ;
	g_Friends_List->Clear() ;
	g_MapTiles_List->Clear() ;
	g_Effect_List->Clear() ;

	if(m_pTutorial!=NULL)
		delete m_pTutorial ;
	if(m_pMenu!=NULL)
		delete m_pMenu ;
	if(m_pEndMenu!=NULL)
		delete m_pEndMenu ;

	for(i=0; i<3; i++)
	{
		if(m_pMenuButton[i]!=NULL)
			delete m_pMenuButton[i] ;
	}
	for(i=0; i<2; i++)
	{
		if(m_pEndMenuButton[i]!=NULL)
			delete m_pEndMenuButton[i] ;
	}
}

Scene* SceneGame::scene()
{
	Scene *scene = new SceneGame ;

	return scene ;
}

void SceneGame::Init()
{
	const float fWinHeight = (float)g_D3dDevice->GetWinHeight() ;

	g_StageProgress->Init() ;

	g_MapTiles_List->LoadMap() ;

	Size MapSize = g_MapTiles_List->GetMapSize() ;
	CCamera *pCamera = new CCamera() ;
	pCamera->SetWorldSize(-32.0f, -32.0f, (MapSize.x*64.0f)-32.0f, (MapSize.y*64.0f)-32.0f) ;
	g_CameraManager->AddCamera(pCamera, 0) ;

	m_pMapBackground = new CMapBackground ;
	m_pMapBackground->Init() ;

	Position HeroPos = g_MapTiles_List->GetHeroPosition() ;
	m_pHero = new CHero ;
	m_pHero->Init() ;
	m_pHero->SetPosition(HeroPos.x * 64.0f + 32.0f, HeroPos.y * 64.0f + 32.0f) ;

	const int nTutorial = g_StageProgress->GetTutorialProgress() ;
	if(nTutorial!=0)
	{
		char filepath[1024] ;
		sprintf_s(filepath, "Resource/Image/Tutorial/Tutorial_%d.png", nTutorial) ;

		pCamera->SetPosition(m_pHero->GetPositionX(), m_pHero->GetPositionY()) ;
		pCamera->CorrectionPosition() ;

		m_pTutorial = new CSprite ;
		m_pTutorial->Init(filepath) ;
		m_pTutorial->SetPosition(pCamera->GetPosition().x, pCamera->GetPosition().y) ;
		
		m_bTutorial = true ;
	}

	m_pMenu = new CSprite ;
	m_pMenu->Init("Resource/Image/Menu/Pause.png") ;

	m_pEndMenu = new CSprite ;
	m_pEndMenu->SetAlpha(0) ;

	m_pMenuButton[0] = new CSprite ;
	m_pMenuButton[0]->Init(292.0f, 84.0f, "Resource/Image/Menu/Button_PContinue.png") ;
	m_pMenuButton[0]->SetTextureUV(292.0f, 0.0f, 584.0f, 84.0f) ;
	
	m_pMenuButton[1] = new CSprite ;
	m_pMenuButton[1]->Init(292.0f, 84.0f, "Resource/Image/Menu/Button_PReplay.png") ;
	m_pMenuButton[1]->SetTextureUV(0.0f, 0.0f, 292.0f, 84.0f) ;

	m_pMenuButton[2] = new CSprite ;
	m_pMenuButton[2]->Init(292.0f, 84.0f, "Resource/Image/Menu/Button_PSelect.png") ;
	m_pMenuButton[2]->SetTextureUV(0.0f, 0.0f, 292.0f, 84.0f) ;

	m_pEndMenuButton[0] = new CSprite ;
	m_pEndMenuButton[0]->Init(296.0f, 78.0f, "Resource/Image/Menu/Button_Replay.png") ;
	m_pEndMenuButton[0]->SetTextureUV(296.0f, 0.0f, 592.0f, 78.0f) ;
	m_pEndMenuButton[0]->SetAlpha(0) ;

	m_pEndMenuButton[1] = new CSprite ;
	m_pEndMenuButton[1]->Init(296.0f, 78.0f, "Resource/Image/Menu/Button_Select.png") ;
	m_pEndMenuButton[1]->SetTextureUV(0.0f, 0.0f, 296.0f, 78.0f) ;
	m_pEndMenuButton[1]->SetAlpha(0) ;

	g_DynamicObjects_List->AddMainCharObjects(m_pHero) ;

	m_pBGM = g_MusicManager->LoadMusic("Resource/Sound/BGM_InGame.mp3", true) ;
	g_MusicManager->PlayMusic(m_pBGM) ;
}

void SceneGame::Destroy()
{
	g_CameraManager->AllCameraClear() ;

	g_MusicManager->StopMusic() ;
	g_MusicManager->StopMusic(2) ;
	g_MusicManager->StopMusic(3) ;
	g_MusicManager->StopMusic(4) ;
}

void SceneGame::Update(float dt)
{
	g_Keyboard->Update() ;
	g_Mouse->Update() ;
	g_Joystick->Update() ;
	g_MusicManager->Loop() ;

	if(m_bTutorial)
	{
		Tutorial() ;
		return ;
	}

	if(m_GameEndMenuState!=NONE)
	{
		GameEndMenu() ;
		return ;
	}

	if(!m_bMenu && g_Keyboard->IsPressDown(DIK_ESCAPE))
	{
		D3DXVECTOR3 CameraPos = g_CameraManager->GetPosition() ;
		float fWinHeight = (float)g_D3dDevice->GetWinHeight() ;

		m_pMenu->SetPosition(CameraPos.x, CameraPos.y) ;
		m_pMenuButton[0]->SetPosition(CameraPos.x, CameraPos.y + ((fWinHeight/2) - 324.0f)) ;
		m_pMenuButton[1]->SetPosition(CameraPos.x, CameraPos.y + ((fWinHeight/2) - 424.0f)) ;
		m_pMenuButton[2]->SetPosition(CameraPos.x, CameraPos.y + ((fWinHeight/2) - 524.0f)) ;

		m_bMenu = true ;
	}

	if(m_bMenu)
	{
		GameMenu() ;
		return ;
	}

	//m_pHero->Update() ;
	g_Friends_List->ReleaseCheck() ;
	g_DynamicObjects_List->Update() ;
	g_MapTiles_List->Update() ;
	
	// Effect Collision
	g_Effect_List->Collision() ;

	// Collision X
	g_CollisionManager->CollisionX() ;

	// Gravity
	g_DynamicObjects_List->Gravity() ;

	// Collision Y
	g_CollisionManager->CollisionY() ;

	// Background Scroll
	m_pMapBackground->Scroll() ;

	// Game_Over or Game_Clear
	if(g_StageProgress->NowStageState()!=g_StageProgress->NONE)
	{
		m_GameEndMenuState = MENU_IN ;
		m_nSelectMenuNum = 0 ;

		if(g_StageProgress->NowStageState()==g_StageProgress->CLEAR)
			m_pEndMenu->Init("Resource/Image/Menu/GameClear.png") ;
		else
			m_pEndMenu->Init("Resource/Image/Menu/GameOver.png") ;

		D3DXVECTOR3 CameraPos = g_CameraManager->GetPosition() ;
		float fWinHeight = (float)g_D3dDevice->GetWinHeight() ;

		m_pEndMenu->SetPosition(CameraPos.x, CameraPos.y) ;
		m_pEndMenuButton[0]->SetPosition(CameraPos.x, CameraPos.y + ((fWinHeight/2) - 450.0f)) ;
		m_pEndMenuButton[1]->SetPosition(CameraPos.x, CameraPos.y + ((fWinHeight/2) - 550.0f)) ;
	}
}

void SceneGame::Render()
{
	g_CameraManager->SetPosition(m_pHero->GetPositionX(), m_pHero->GetPositionY()) ;
	g_CameraManager->CameraRun() ;

	m_pMapBackground->Render() ;

	g_MapTiles_List->Render() ;
	g_Friends_List->Render() ;
	m_pHero->Render() ;

	if(m_bMenu)
	{
		m_pMenu->Render() ;
		for(int i=0; i<3; i++)
			m_pMenuButton[i]->Render() ;
	}

	if(m_GameEndMenuState!=NONE)
	{
		m_pEndMenu->Render() ;
		for(int i=0; i<2; i++)
			m_pEndMenuButton[i]->Render() ;
	}

	if(m_bTutorial)
		m_pTutorial->Render() ;
}

void SceneGame::Tutorial()
{
	if(g_Keyboard->IsPressDown(DIK_RETURN) || g_Keyboard->IsPressDown(DIK_SPACE) || g_Keyboard->IsPressDown(DIK_Z))
		m_bTutorial = false ;
}

void SceneGame::GameMenu()
{
	MenuButtonMove(m_pMenuButton, 292.0f, 84.0f, 3) ;
		
	if(g_Keyboard->IsPressDown(DIK_RETURN) || g_Keyboard->IsPressDown(DIK_SPACE) || g_Keyboard->IsPressDown(DIK_Z))
	{
		if(m_nSelectMenuNum==0)
		{
			m_bMenu = false ;
		}
		else if(m_nSelectMenuNum==1)
		{
			g_SceneManager->ChangeScene(SceneGame::scene()) ;
			return ;
		}
		else
		{
			g_SceneManager->ChangeScene(SceneStageSelect::scene()) ;
			return ;
		}
	}
}

void SceneGame::GameEndMenu()
{
	if(m_GameEndMenuState==MENU_IN)
	{
		int nAlpha = (int)((m_fTime / 1.0f) * 255.0f) ;
		m_pEndMenu->SetAlpha(nAlpha) ;

		if(m_fTime>=1.0f)
		{
			m_fTime = 0.0f ;
			m_GameEndMenuState = BUTTON_IN ;
			m_pEndMenu->SetAlpha(255) ;

			// 임시 엔딩으로 넘어가기
			if(g_StageProgress->LastStageClear())
				g_SceneManager->ChangeScene(SceneCredit::scene()) ;

			return ;
		}

		m_fTime += g_D3dDevice->GetTime() ;
	}
	else if(m_GameEndMenuState==BUTTON_IN)
	{
		int i ;
		int nAlpha = (int)((m_fTime / 1.0f) * 255.0f) ;
		for(i=0; i<2; i++)
			m_pEndMenuButton[i]->SetAlpha(nAlpha) ;

		if(m_fTime>=1.0f)
		{
			m_fTime = 0.0f ;
			m_GameEndMenuState = SHOW ;
			for(i=0; i<2; i++)
				m_pEndMenuButton[i]->SetAlpha(255) ;

			return ;
		}

		m_fTime += g_D3dDevice->GetTime() ;
	}
	else
	{
		MenuButtonMove(m_pEndMenuButton, 296.0f, 78.0f, 2) ;
		
		if(g_Keyboard->IsPressDown(DIK_RETURN) || g_Keyboard->IsPressDown(DIK_SPACE) || g_Keyboard->IsPressDown(DIK_Z))
		{
			if(m_nSelectMenuNum==0)
			{
				g_SceneManager->ChangeScene(SceneGame::scene()) ;
				return ;
			}
			else
			{
				g_SceneManager->ChangeScene(SceneStageSelect::scene()) ;
				return ;
			}
		}
	}
}

void SceneGame::MenuButtonMove(CSprite **pMenuButton, const float fWidth, const float fHeight, const int nMaxMenu)
{
	int prevSelectNum = m_nSelectMenuNum ;

	if(g_Keyboard->IsPressDown(DIK_UP))
		--m_nSelectMenuNum ;
	else if(g_Keyboard->IsPressDown(DIK_DOWN))
		++m_nSelectMenuNum ;

	if(m_nSelectMenuNum>=nMaxMenu)
		m_nSelectMenuNum -= nMaxMenu ;
	else if(m_nSelectMenuNum<0)
		m_nSelectMenuNum += nMaxMenu ;

	if(prevSelectNum!=m_nSelectMenuNum)
	{
		pMenuButton[prevSelectNum]->SetTextureUV(0.0f, 0.0f, fWidth, fHeight) ;
		pMenuButton[m_nSelectMenuNum]->SetTextureUV(fWidth, 0.0f, fWidth*2.0f, fHeight) ;
	}
}