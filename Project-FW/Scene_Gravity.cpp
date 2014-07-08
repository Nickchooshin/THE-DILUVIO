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

	for(int i=0; i<5; i++)
	{
		m_pTiles[i] = new CTilesGround ;
		m_pTiles[i]->Init() ;
	}
	m_pTiles[0]->SetPosition(320.0f, 0.0f) ;
	m_pTiles[1]->SetPosition(384.0f, 0.0f) ;
	m_pTiles[2]->SetPosition(384.0f, 64.0f) ;
	m_pTiles[3]->SetPosition(448.0f, 0.0f) ;
	m_pTiles[4]->SetPosition(192.0f, 96.0f) ;

	m_pCrash = new CCrashChecker ;
}

void SceneGravity::Destroy()
{
	delete m_pHero ;
	delete m_pCrash ;

	for(int i=0; i<5; i++)
		delete m_pTiles[i] ;
}

void SceneGravity::Update(float dt)
{
	g_Keyboard->Update() ;
	g_Mouse->Update() ;
	g_Joystick->Update() ;
	g_MusicManager->Loop() ;

	m_pHero->Update() ;

	for(int i=0; i<5; i++)
		m_pCrash->XCollision(m_pHero, m_pTiles[i]) ;
	m_pHero->Gravity() ;
	for(int i=0; i<5; i++)
		m_pCrash->YCollision(m_pHero, m_pTiles[i]) ;
}

void SceneGravity::Render()
{
	g_CameraManager->CameraRun() ;

	m_pHero->Render() ;

	for(int i=0; i<5; i++)
		m_pTiles[i]->Render() ;
}