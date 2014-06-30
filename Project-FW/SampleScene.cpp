#include "SampleScene.h"

#include "Keyboard.h"
#include "Mouse.h"
#include "Joystick.h"

#include "Sprite.h"
#include "UISprite.h"
#include "CameraManager.h"
#include "MusicManager.h"

const int sprite_max=1000 ;

CSprite Sprite, Sprite2 ;
CUISprite UISprite, UISprite2 ;
FMOD::Sound *sound[3] ;

SampleScene::SampleScene()
{
}
SampleScene::~SampleScene()
{
}

Scene* SampleScene::scene()
{
	Scene *scene = new SampleScene ;

	return scene ;
}

void SampleScene::Init()
{
	g_CameraManager->AddCamera(new CCamera(), 0) ;
	g_CameraManager->AddCamera(new CCamera(), 1) ;
	g_CameraManager->MovePosition(50.0f, 50.0f, 1) ;

	Sprite.Init(50.0f, 50.0f, "sample_texture.png") ;
	Sprite.SetTextureUV(0.0f, 0.0f, 50.0f, 50.0f) ;
	Sprite.SetPositionZ(0.0f) ;
	UISprite.Init(60.0f, 80.0f, "sample_texture2.png") ;
	UISprite.Init("sample_texture2.png") ;

	Sprite2.Init("sample_texture2.png") ;
	UISprite2.Init("sample_texture2.png") ;

	sound[0] = g_MusicManager->LoadMusic("click_1.mp3", false, false) ;
	sound[1] = g_MusicManager->LoadMusic("click_2.mp3", false, false) ;
	sound[2] = g_MusicManager->LoadMusic("eat.mp3", false, false) ;
}

void SampleScene::Destroy()
{
}

void SampleScene::Update(float dt)
{
	g_Keyboard->Update() ;
	g_Mouse->Update() ;
	g_Joystick->Update() ;
	g_MusicManager->Loop() ;

	static float x=0.0f, y=0.0f ;

	if(g_Keyboard->IsButtonDown(DIK_UP))
	{
		y += 1.5f ;
	}
	if(g_Keyboard->IsButtonDown(DIK_DOWN))
	{
		y -= 1.5f ;
	}
	if(g_Keyboard->IsButtonDown(DIK_RIGHT))
	{
		x += 1.5f ;
	}
	if(g_Keyboard->IsButtonDown(DIK_LEFT))
	{
		x -= 1.5f ;
	}

	if(g_Keyboard->IsButtonDown(DIK_1))
	{
		Sprite.SetTextureUV(0.0f, 0.0f, 50.0f, 50.0f) ;
	}
	if(g_Keyboard->IsButtonDown(DIK_2))
	{
		Sprite.SetTextureUV(50.0f, 0.0f, 100.0f, 50.0f) ;
	}
	if(g_Keyboard->IsButtonDown(DIK_3))
	{
		Sprite.SetTextureUV(0.0f, 50.0f, 50.0f, 100.0f) ;
	}
	if(g_Keyboard->IsButtonDown(DIK_4))
	{
		Sprite.SetTextureUV(50.0f, 50.0f, 100.0f, 100.0f) ;
	}

	if(g_Keyboard->IsButtonDown(DIK_8))
	{
		Sprite.SetPositionZ(0.0f) ;
	}
	if(g_Keyboard->IsButtonDown(DIK_9))
	{
		Sprite.SetPositionZ(1.0f) ;
	}
	if(g_Keyboard->IsButtonDown(DIK_0))
	{
		Sprite.SetPositionZ(0.5f) ;
	}

	if(g_Keyboard->IsButtonDown(DIK_5))
	{
		UISprite.SetPositionZ(0.0f) ;
		UISprite2.SetPositionZ(0.0f) ;
	}
	if(g_Keyboard->IsButtonDown(DIK_6))
	{
		UISprite.SetPositionZ(1.0f) ;
		UISprite2.SetPositionZ(0.0f) ;
	}
	if(g_Keyboard->IsButtonDown(DIK_7))
	{
		UISprite.SetPositionZ(0.0f) ;
		UISprite2.SetPositionZ(1.0f) ;
	}

	if(g_Keyboard->IsButtonDown(DIK_F1))
	{
		g_CameraManager->SetCamera(0) ;
	}
	if(g_Keyboard->IsButtonDown(DIK_F2))
	{
		g_CameraManager->SetCamera(1) ;
	}
	
	if(g_Mouse->IsMouse(g_Mouse->LBUTTON_DOWN))
	{
		g_MusicManager->PlayMusic(sound[0]) ;
	}
	if(g_Mouse->IsMouse(g_Mouse->RBUTTON_DOWN))
	{
		g_MusicManager->PlayMusic(sound[2]) ;
	}
	if(g_Keyboard->IsButtonDown(DIK_SPACE))
	{
		g_MusicManager->PlayMusic(sound[1]) ;
	}

	/*if(g_Mouse->IsMouse(g_Mouse->LBUTTON_DOWN))
	{
		MessageBox(NULL, "LBUTTON_DOWN", "LBUTTON_DOWN", MB_OK) ;
	}

	if(g_Joystick->IsButtonDown(0))
	{
		MessageBox(NULL, "0 Button", "0 BUtton", MB_OK) ;
	}
	if(g_Joystick->IsButtonDown(1))
	{
		MessageBox(NULL, "1 Button", "1 BUtton", MB_OK) ;
	}
	if(g_Joystick->IsButtonDown(3))
	{
		MessageBox(NULL, "3 Button", "3 BUtton", MB_OK) ;
	}
	if(g_Joystick->IsButtonDown(4))
	{
		MessageBox(NULL, "4 Button", "4 BUtton", MB_OK) ;
	}
	if(g_Joystick->IsAxisMin(1000, 'x'))
	{
		MessageBox(NULL, "X 1000", "X 1000", MB_OK) ;
	}
	if(g_Joystick->IsPov(22500))
	{
		MessageBox(NULL, "POV ก็", "POV ก็", MB_OK) ;
	}*/

	Sprite.SetPosition(x, y) ;
	Sprite2.SetPosition(100.0f, 100.0f) ;
	UISprite.SetPosition(100.0f, 100.0f) ;
	UISprite2.SetPosition(50.0f, 50.0f) ;
}

void SampleScene::Render()
{
	g_CameraManager->CameraRun() ;
	
	Sprite.Render() ;
	//UISprite.Render() ;
	//Sprite2.Render() ;
	//UISprite2.Render() ;
}