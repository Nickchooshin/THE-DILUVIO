#include "Scene_Credit.h"
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

SceneCredit::SceneCredit() : m_pBackground(NULL), m_pCredit(NULL),
							 m_pBlank(NULL),
							 m_bFadeIn(true), m_bFadeOut(false),
							 m_fTime(0.0f), m_fFadeTime(0.0f),
							 m_pBGM(NULL)
{
}
SceneCredit::~SceneCredit()
{
	if(m_pBackground!=NULL)
		delete m_pBackground ;
	if(m_pCredit!=NULL)
		delete m_pCredit ;
	if(m_pBlank!=NULL)
		delete m_pBlank ;
}

Scene* SceneCredit::scene()
{
	Scene *scene = new SceneCredit ;

	return scene ;
}

void SceneCredit::Init()
{
	float fWinWidth = (float)g_D3dDevice->GetWinWidth() ;
	float fWinHeight = (float)g_D3dDevice->GetWinHeight() ;
	
	g_CameraManager->AllCameraClear() ;
	g_CameraManager->AddCamera(new CCamera()) ;

	m_pBackground = new CSprite ;
	m_pBackground->Init("Resource/Image/Credit/Background.png") ;
	m_pBackground->SetPosition(fWinWidth / 2.0f, fWinHeight / 2.0f) ;

	m_pCredit = new CSprite ;
	m_pCredit->Init("Resource/Image/Credit/Credit.png") ;
	m_pCredit->SetPosition(fWinWidth - 256.0f, -1000.0f) ;

	m_pBlank = new CSprite ;
	m_pBlank->Init(fWinWidth, fWinHeight, "Resource/Image/blank.png") ;
	m_pBlank->SetPosition(fWinWidth / 2.0f, fWinHeight / 2.0f) ;
	m_pBlank->SetRGB(0, 0, 0) ;
	m_pBlank->SetAlpha(255) ;
	
	m_pBGM = g_MusicManager->LoadMusic("Resource/Sound/BGM_Credit.mp3", true, true) ;
	g_MusicManager->PlayMusic(m_pBGM) ;
}

void SceneCredit::Destroy()
{
	g_MusicManager->StopMusic() ;
}

void SceneCredit::Update(float dt)
{
	g_Keyboard->Update() ;
	g_Mouse->Update() ;
	g_Joystick->Update() ;
	g_MusicManager->Loop() ;

	m_pCredit->SetPositionY(-1000.0f + ((m_fTime / 75.0f) * 3000.0f)) ;

	m_fTime += g_D3dDevice->GetTime() ;
	if(m_fTime>=75.0f || (!m_bFadeIn && (g_Keyboard->IsPressDown(DIK_RETURN) || g_Keyboard->IsPressDown(DIK_SPACE) || g_Keyboard->IsPressDown(DIK_ESCAPE))))
		m_bFadeOut = true ;

	if(m_bFadeIn)
	{
		m_pBlank->SetAlpha(255 - (int)(m_fFadeTime / 5.0f * 255.0f)) ;

		m_fFadeTime += g_D3dDevice->GetTime() ;

		if(m_fFadeTime>=5.0f)
		{
			m_bFadeIn = false ;
			m_fFadeTime = 0.0f ;
		}
	}
	else if(m_bFadeOut)
	{
		m_pBlank->SetAlpha((int)(m_fFadeTime / 5.0f * 255.0f)) ;

		m_fFadeTime += g_D3dDevice->GetTime() ;

		if(m_fFadeTime>=5.0f)
		{
			g_SceneManager->ChangeScene(SceneTitle::scene()) ;
			return ;
		}
	}
}

void SceneCredit::Render()
{
	g_CameraManager->CameraRun() ;

	m_pBackground->Render() ;
	m_pCredit->Render() ;

	if(m_bFadeIn || m_bFadeOut)
		m_pBlank->Render() ;
}