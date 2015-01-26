#include "Scene_Logo.h"
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

SceneLogo::SceneLogo() : m_pBlank(NULL),
						 m_pTeamLogo(NULL), m_pTeamLogoMono(NULL),
						 m_pGameLogo(NULL),
						 m_pWarningLogo(NULL),
						 m_fTime(0.0f),
						 m_LogoState(TEAMLOGOMONO_IN)
{
}
SceneLogo::~SceneLogo()
{
	if(m_pBlank!=NULL)
		delete m_pBlank ;
	if(m_pTeamLogo!=NULL)
		delete m_pTeamLogo ;
	if(m_pTeamLogoMono!=NULL)
		delete m_pTeamLogoMono ;
	if(m_pGameLogo!=NULL)
		delete m_pGameLogo ;
	if(m_pWarningLogo!=NULL)
		delete m_pWarningLogo ;
}

Scene* SceneLogo::scene()
{
	Scene *scene = new SceneLogo ;

	return scene ;
}

void SceneLogo::Init()
{
	float fWinWidth = (float)g_D3dDevice->GetWinWidth() ;
	float fWinHeight = (float)g_D3dDevice->GetWinHeight() ;
	
	g_CameraManager->AllCameraClear() ;
	g_CameraManager->AddCamera(new CCamera()) ;

	m_pBlank = new CSprite ;
	m_pBlank->Init(1024.0f, 768.0f, "Resource/Image/blank.png") ;
	m_pBlank->SetPosition(fWinWidth / 2.0f, fWinHeight / 2.0f) ;

	m_pTeamLogo = new CSprite ;
	m_pTeamLogo->Init("Resource/Image/Logo/Team_Logo.png") ;
	m_pTeamLogo->SetPosition(fWinWidth / 2.0f, fWinHeight / 2.0f) ;
	m_pTeamLogo->SetAlpha(0) ;

	m_pTeamLogoMono = new CSprite ;
	m_pTeamLogoMono->Init("Resource/Image/Logo/Team_Logo_Mono.png") ;
	m_pTeamLogoMono->SetPosition(fWinWidth / 2.0f, fWinHeight / 2.0f) ;
	m_pTeamLogoMono->SetAlpha(0) ;

	m_pGameLogo = new CSprite ;
	m_pGameLogo->Init("Resource/Image/Logo/Game_Logo.png") ;
	m_pGameLogo->SetPosition(fWinWidth / 2.0f, fWinHeight / 2.0f) ;

	m_pWarningLogo = new CSprite ;
	m_pWarningLogo->Init("Resource/Image/Logo/Warning_Logo.png") ;
	m_pWarningLogo->SetPosition(fWinWidth / 2.0f, fWinHeight / 2.0f) ;

	m_pBGM = g_MusicManager->LoadMusic("Resource/Sound/SE_Team_Logo.mp3", false, false) ;
	g_MusicManager->PlayMusic(m_pBGM) ;
}

void SceneLogo::Destroy()
{
}

void SceneLogo::Update(float dt)
{
	g_Keyboard->Update() ;
	g_Mouse->Update() ;
	g_Joystick->Update() ;
	g_MusicManager->Loop() ;

	if(m_LogoState==TEAMLOGOMONO_IN)
	{
		m_pTeamLogoMono->SetAlpha((int)(m_fTime / 0.5f * 255.0f)) ;

		if(m_fTime>=0.5f)
		{
			m_pTeamLogoMono->SetAlpha(255) ;

			m_fTime -= 0.5f ;
			m_LogoState = TEAMLOGO_IN ;
			return ;
		}
	}
	else if(m_LogoState==TEAMLOGO_IN)
	{
		m_pTeamLogoMono->SetAlpha(255 - (int)(m_fTime / 0.5f * 255.0f)) ;
		m_pTeamLogo->SetAlpha((int)(m_fTime / 0.5f * 255.0f)) ;

		if(m_fTime>=0.5f)
		{
			m_pTeamLogoMono->SetAlpha(0) ;
			m_pTeamLogo->SetAlpha(255) ;

			m_fTime -= 0.5f ;
			m_LogoState = TEAMLOGO ;
			return ;
		}
	}
	else if(m_LogoState==TEAMLOGO)
	{
		if(m_fTime>=1.0f)
		{
			m_fTime -= 1.0f ;
			m_LogoState = TEAMLOGO_OUT ;
			return ;
		}
	}
	else if(m_LogoState==TEAMLOGO_OUT)
	{
		m_pTeamLogoMono->SetAlpha((int)(m_fTime / 0.5f * 255.0f)) ;
		m_pTeamLogo->SetAlpha(255 - (int)(m_fTime / 0.5f * 255.0f)) ;
		
		if(m_fTime>=0.5f)
		{
			m_pTeamLogoMono->SetAlpha(255) ;
			m_pTeamLogo->SetAlpha(0) ;

			m_fTime -= 0.5f ;
			m_LogoState = TEAMLOGOMONO_OUT ;
			return ;
		}
	}
	else if(m_LogoState==TEAMLOGOMONO_OUT)
	{
		m_pTeamLogoMono->SetAlpha(255 - (int)(m_fTime / 0.5f * 255.0f)) ;

		if(m_fTime>=0.5f)
		{
			m_pTeamLogoMono->SetAlpha(0) ;

			m_fTime -= 0.5f ;
			g_SceneManager->ChangeScene(SceneTitle::scene()) ;
			return ;
		}
	}

	m_fTime += g_D3dDevice->GetTime() ;
}

void SceneLogo::Render()
{
	g_CameraManager->CameraRun() ;

	m_pBlank->Render() ;

	m_pTeamLogoMono->Render() ;
	m_pTeamLogo->Render() ;
}