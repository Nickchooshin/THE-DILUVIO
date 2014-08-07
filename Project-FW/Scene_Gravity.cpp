#include "Scene_Gravity.h"

#include "Keyboard.h"
#include "Mouse.h"
#include "Joystick.h"

#include "Sprite.h"
#include "UISprite.h"
#include "CameraManager.h"
#include "MusicManager.h"

#include "Hero.h"

#include "MapTiles_List.h"
#include "Friends_List.h"
#include "DynamicObjects_List.h"
#include "Effect_List.h"

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
	g_MapTiles_List->LoadMap(4) ;

	Size MapSize = g_MapTiles_List->GetMapSize() ;
	CCamera *pCamera = new CCamera() ;
	pCamera->SetWorldSize(-32.0f, -32.0f, (MapSize.x*64.0f)-32.0f, (MapSize.y*64.0f)-32.0f) ;
	g_CameraManager->AllCameraClear() ;
	g_CameraManager->AddCamera(pCamera, 0) ;

	Position HeroPos = g_MapTiles_List->GetHeroPosition() ;
	m_pHero = new CHero ;
	m_pHero->Init() ;
	m_pHero->SetPosition(HeroPos.x * 64.0f + 32.0f, HeroPos.y * 64.0f + 32.0f) ;

	//
	g_DynamicObjects_List->AddMainCharObjects(m_pHero) ;
}

void SceneGravity::Destroy()
{
	delete m_pHero ;
}

void SceneGravity::Update(float dt)
{
	g_Keyboard->Update() ;
	g_Mouse->Update() ;
	g_Joystick->Update() ;
	g_MusicManager->Loop() ;

	//m_pHero->Update() ;
	g_Friends_List->ReleaseCheck() ;
	g_DynamicObjects_List->Update() ;
	g_MapTiles_List->Update() ;

	// Collision X
	g_MapTiles_List->Collision('x') ;

	g_DynamicObjects_List->Collision('x') ;

	// Gravity
	g_DynamicObjects_List->Gravity() ;

	// Collision Y
	g_MapTiles_List->Collision('y') ;

	g_DynamicObjects_List->Collision('y') ;

	// Effect Collision
	g_Effect_List->Collision() ;
}

void SceneGravity::Render()
{
	g_CameraManager->SetPosition(m_pHero->GetPositionX(), m_pHero->GetPositionY()) ;
	g_CameraManager->CameraRun() ;

	g_MapTiles_List->Render() ;
	g_Friends_List->Render() ;
	m_pHero->Render() ;

	/*CSprite sprite ;
	sprite.Init("Resource/Image/collision.png") ;
	//sprite.SetCenterPosition(0.0f, 0.0f) ;
	sprite.Render() ;*/
}