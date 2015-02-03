#include "Scene_Extra.h"
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

SceneExtra::SceneExtra() : m_pBackground(NULL)
{
}
SceneExtra::~SceneExtra()
{
	if(m_pBackground!=NULL)
		delete m_pBackground ;
}

Scene* SceneExtra::scene()
{
	Scene *scene = new SceneExtra ;

	return scene ;
}

void SceneExtra::Init()
{
	float fWinWidth = (float)g_D3dDevice->GetWinWidth() ;
	float fWinHeight = (float)g_D3dDevice->GetWinHeight() ;
	
	g_CameraManager->AllCameraClear() ;
	g_CameraManager->AddCamera(new CCamera()) ;

	m_pBackground = new CSprite ;
	m_pBackground->Init("Resource/Image/Extra/Background.png") ;
	m_pBackground->SetPosition(fWinWidth / 2.0f, fWinHeight / 2.0f) ;
}

void SceneExtra::Destroy()
{
	g_MusicManager->StopMusic() ;
}

void SceneExtra::Update(float dt)
{
	g_Keyboard->Update() ;
	g_Mouse->Update() ;
	g_Joystick->Update() ;
	g_MusicManager->Loop() ;

	if(g_Keyboard->IsPressDown(DIK_ESCAPE))
		g_SceneManager->ChangeScene(SceneTitle::scene()) ;
}

void SceneExtra::Render()
{
	g_CameraManager->CameraRun() ;

	m_pBackground->Render() ;
}