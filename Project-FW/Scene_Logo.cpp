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

SceneLogo::SceneLogo() : m_pTeamLogo(NULL), m_pTeamLogoMono(NULL),
						 m_pGameLogo(NULL),
						 m_pWarningLogo(NULL)
{
}
SceneLogo::~SceneLogo()
{
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
	Scene *scene = new SceneTitle ;

	return scene ;
}

void SceneLogo::Init()
{
	float fWinWidth = (float)g_D3dDevice->GetWinWidth() ;
	float fWinHeight = (float)g_D3dDevice->GetWinHeight() ;

	m_pTeamLogo = new CSprite ;
	m_pTeamLogo->Init("Resource/Image/Logo/Team_Logo.png") ;
	m_pTeamLogo->SetPosition(fWinWidth / 2.0f, fWinHeight / 2.0f) ;

	m_pTeamLogoMono = new CSprite ;
	m_pTeamLogoMono->Init("Resource/Image/Logo/Team_Logo_Mono.png") ;
	m_pTeamLogoMono->SetPosition(fWinWidth / 2.0f, fWinHeight / 2.0f) ;

	m_pGameLogo = new CSprite ;
	m_pGameLogo->Init("Resource/Image/Logo/Game_Logo.png") ;
	m_pGameLogo->SetPosition(fWinWidth / 2.0f, fWinHeight / 2.0f) ;

	m_pWarningLogo = new CSprite ;
	m_pWarningLogo->Init("Resource/Image/Logo/Warning_Logo.png") ;
	m_pWarningLogo->SetPosition(fWinWidth / 2.0f, fWinHeight / 2.0f) ;
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

	g_SceneManager->ChangeScene(SceneTitle::scene()) ;
}

void SceneLogo::Render()
{
	g_CameraManager->CameraRun() ;
}