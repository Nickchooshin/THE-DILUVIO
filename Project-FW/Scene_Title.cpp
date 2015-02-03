#include "Scene_Title.h"
#include "Scene_StageSelect.h"
#include "Scene_Extra.h"

#include "Keyboard.h"
#include "Mouse.h"
#include "Joystick.h"

#include "Sprite.h"
#include "UISprite.h"
#include "CameraManager.h"
#include "MusicManager.h"
#include "SceneManager.h"

#include "D3dDevice.h"

SceneTitle::SceneTitle() : m_pBackground(NULL),
						   m_pBlank(NULL),
						   m_nMenuNum(0),
						   m_nHelpNum(0),
						   m_bFadeOut(false),
						   m_fTime(0.0f),
						   m_pBGM(NULL), m_pSEButton(NULL)
{
	for(int i=0; i<4; i++)
	{
		m_pButton[i] = NULL ;
		m_pHelp[i] = NULL ;
	}
}
SceneTitle::~SceneTitle()
{
	if(m_pBackground!=NULL)
		delete m_pBackground ;

	if(m_pBlank!=NULL)
		delete m_pBlank ;

	for(int i=0; i<4; i++)
	{
		delete m_pButton[i] ;
		delete m_pHelp[i] ;
	}
}

Scene* SceneTitle::scene()
{
	Scene *scene = new SceneTitle ;

	return scene ;
}

void SceneTitle::Init()
{
	float fWinWidth = (float)g_D3dDevice->GetWinWidth() ;
	float fWinHeight = (float)g_D3dDevice->GetWinHeight() ;
	
	g_CameraManager->AllCameraClear() ;
	g_CameraManager->AddCamera(new CCamera()) ;

	m_pBackground = new CSprite ;
	m_pBackground->Init("Resource/Image/Title/Background.png") ;
	m_pBackground->SetPosition(fWinWidth / 2.0f, fWinHeight / 2.0f) ;

	m_pButton[0] = new CSprite ;
	m_pButton[0]->Init(212.0f, 122.0f, "Resource/Image/Title/Button_Start.png") ;
	m_pButton[0]->SetTextureUV(212.0f, 0.0f, 424.0f, 122.0f) ;
	m_pButton[0]->SetPosition(921.0f, fWinHeight - 331.0f) ;

	m_pButton[1] = new CSprite ;
	m_pButton[1]->Init(212.0f, 122.0f, "Resource/Image/Title/Button_Extra.png") ;
	m_pButton[1]->SetTextureUV(0.0f, 0.0f, 212.0f, 122.0f) ;
	m_pButton[1]->SetPosition(921.0f, fWinHeight - 452.0f) ;

	m_pButton[2] = new CSprite ;
	m_pButton[2]->Init(212.0f, 122.0f, "Resource/Image/Title/Button_Help.png") ;
	m_pButton[2]->SetTextureUV(0.0f, 0.0f, 212.0f, 122.0f) ;
	m_pButton[2]->SetPosition(921.0f, fWinHeight - 572.0f) ;

	m_pButton[3] = new CSprite ;
	m_pButton[3]->Init(212.0f, 122.0f, "Resource/Image/Title/Button_Exit.png") ;
	m_pButton[3]->SetTextureUV(0.0f, 0.0f, 212.0f, 122.0f) ;
	m_pButton[3]->SetPosition(921.0f, fWinHeight - 693.0f) ;

	char filepath[1024] ;
	for(int i=0; i<4; i++)
	{
		sprintf_s(filepath, "Resource/Image/Help/Help%d.png", i+1) ;
		m_pHelp[i] = new CSprite ;
		m_pHelp[i]->Init(filepath) ;
		m_pHelp[i]->SetPosition(fWinWidth / 2.0f, fWinHeight / 2.0f) ;
	}

	m_pBlank = new CSprite ;
	m_pBlank->Init(fWinWidth, fWinHeight, "Resource/Image/blank.png") ;
	m_pBlank->SetPosition(fWinWidth / 2.0f, fWinHeight / 2.0f) ;
	m_pBlank->SetRGB(0, 0, 0) ;
	m_pBlank->SetAlpha(0) ;
	
	m_pBGM = g_MusicManager->LoadMusic("Resource/Sound/BGM_Title.mp3", true, true) ;
	m_pSEButton = g_MusicManager->LoadMusic("Resource/Sound/SE_Button.mp3", false, false) ;
	g_MusicManager->PlayMusic(m_pBGM) ;
}

void SceneTitle::Destroy()
{
	g_MusicManager->StopMusic() ;
}

void SceneTitle::Update(float dt)
{
	g_Keyboard->Update() ;
	g_Mouse->Update() ;
	g_Joystick->Update() ;
	g_MusicManager->Loop() ;

	if(m_bFadeOut)
	{
		FadeOut() ;
		return ;
	}
	else if(m_nHelpNum!=0)
	{
		HelpMenu() ;
		return ;
	}

	MenuSelect() ;

	if(g_Keyboard->IsPressDown(DIK_RETURN) || g_Keyboard->IsPressDown(DIK_SPACE))
	{
		g_MusicManager->PlayMusic(m_pSEButton, 5) ;

		switch(m_nMenuNum)
		{
		case 0 :
		case 1 :
		case 3 :
			m_bFadeOut = true ;
			return ;

		case 2 :
			m_nHelpNum = 1 ;
			return ;
		}
	}
}

void SceneTitle::Render()
{
	g_CameraManager->CameraRun() ;

	m_pBackground->Render() ;

	for(int i=0; i<4; i++)
		m_pButton[i]->Render() ;

	if(m_nHelpNum!=0)
		m_pHelp[m_nHelpNum-1]->Render() ;

	if(m_bFadeOut)
		m_pBlank->Render() ;
}

void SceneTitle::MenuSelect()
{
	const int prevMenuNum = m_nMenuNum ;

	if(g_Keyboard->IsPressDown(DIK_UP))
	{
		if(m_nMenuNum>0)
			--m_nMenuNum ;
	}
	if(g_Keyboard->IsPressDown(DIK_DOWN))
	{
		if(m_nMenuNum<3)
			++m_nMenuNum ;
	}

	if(m_nMenuNum!=prevMenuNum)
	{
		m_pButton[prevMenuNum]->SetTextureUV(0.0f, 0.0f, 212.0f, 122.0f) ;
		m_pButton[m_nMenuNum]->SetTextureUV(212.0f, 0.0f, 424.0f, 122.0f) ;
	}
}

void SceneTitle::HelpMenu()
{
	if(g_Keyboard->IsPressDown(DIK_RETURN) || g_Keyboard->IsPressDown(DIK_SPACE))
	{
		++m_nHelpNum ;
		if(m_nHelpNum>4)
			m_nHelpNum = 0 ;
	}
}

void SceneTitle::FadeOut()
{
	int nAlpha = (int)((m_fTime / 1.0f) * 255.0f) ;
	m_pBlank->SetAlpha(nAlpha) ;

	if(m_fTime>=1.0f)
	{
		m_pBlank->SetAlpha(255) ;

		switch(m_nMenuNum)
		{
		case 0 :
			g_SceneManager->ChangeScene(SceneStageSelect::scene()) ;
			return ;

		case 1 :
			g_SceneManager->ChangeScene(SceneExtra::scene()) ;
			return ;

		case 3 :
			PostQuitMessage(0) ;
			return ;
		}
	}

	m_fTime += g_D3dDevice->GetTime() ;
}