#include "Scene_Gravity.h"

#include "Keyboard.h"
#include "Mouse.h"
#include "Joystick.h"

#include "Sprite.h"
#include "UISprite.h"
#include "CameraManager.h"
#include "MusicManager.h"

#include "Hero.h"
#include "Tiles_Ground.h"
#include "CrashChecker.h"

SceneGravity::SceneGravity()
{
}
SceneGravity::~SceneGravity()
{
}

Scene* SceneGravity::scene()
{
	Scene *scene = new SceneGravity ;

	return scene ;
}

void SceneGravity::Init()
{
	g_CameraManager->AllCameraClear() ;
	g_CameraManager->AddCamera(new CCamera(), 0) ;

	m_pHero = new CHero ;
	m_pHero->Init() ;
	m_pHero->SetPosition(50.0f, 50.0f) ;

	m_pTile = new CTilesGround ;
	m_pTile->Init() ;
	//m_pTile->SetPosition(640.0f, 0.0f) ;
	m_pTile->SetPosition(320.0f, 0.0f) ;

	m_pCrash = new CCrashChecker ;
}

void SceneGravity::Destroy()
{
	delete m_pHero ;
	delete m_pTile ;
	delete m_pCrash ;
}

void SceneGravity::Update(float dt)
{
	g_Keyboard->Update() ;
	g_Mouse->Update() ;
	g_Joystick->Update() ;
	g_MusicManager->Loop() ;

	m_pHero->Update() ;

	m_pCrash->Crash_CharAndTile(m_pHero, m_pTile) ;
}

void SceneGravity::Render()
{
	g_CameraManager->CameraRun() ;

	m_pHero->Render() ;
	m_pTile->Render() ;
}