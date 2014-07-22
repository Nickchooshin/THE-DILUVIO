#include "Scene_Gravity.h"

#include "Keyboard.h"
#include "Mouse.h"
#include "Joystick.h"

#include "Sprite.h"
#include "UISprite.h"
#include "CameraManager.h"
#include "MusicManager.h"

#include "Hero.h"
#include "MapTiles.h"
#include "Collision.h"

//
#include "Friends_List.h"
#include "Friends.h"

#include "Collision.h"
//

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
	m_pHero->SetPosition(50.0f, 250.0f) ;

	m_MapTiles = new CMapTiles ;
	m_MapTiles->LoadMap(1) ;
	m_pHero->SetMapTiles(m_MapTiles) ;

	m_pCollision = new CCollision ;
}

void SceneGravity::Destroy()
{
	delete m_pHero ;
	delete m_MapTiles ;
	delete m_pCollision ;
}

void SceneGravity::Update(float dt)
{
	g_Keyboard->Update() ;
	g_Mouse->Update() ;
	g_Joystick->Update() ;
	g_MusicManager->Loop() ;

	m_pHero->Update() ;
	g_Friends_List->Update() ;

	//
	int size = g_Friends_List->GetSize() ;

	// Add Collision Object List
	m_MapTiles->ClearCollisionList() ;
	m_MapTiles->AddCollisionList(m_pHero) ;
	for(int i=0; i<size; i++)
	{
		CFriends *pFriend = g_Friends_List->GetFriend(i) ;
		if(pFriend->GetRelease())
			m_MapTiles->AddCollisionList(pFriend) ;
	}

	// Collision X
	m_MapTiles->Collision('x') ;

	g_Friends_List->Collision('x') ;
	g_Friends_List->Collision(m_pHero, 'x') ;

	// Gravity
	m_pHero->Gravity() ;
	g_Friends_List->Gravity() ;


	// Collision Y
	m_MapTiles->Collision('y') ;

	g_Friends_List->Collision('y') ;
	g_Friends_List->Collision(m_pHero, 'y') ;
}

void SceneGravity::Render()
{
	g_CameraManager->CameraRun() ;

	m_MapTiles->Render() ;
	g_Friends_List->Render() ;
	m_pHero->Render() ;

	/*CSprite sprite ;
	sprite.Init("Resource/Image/collision.png") ;
	//sprite.SetCenterPosition(0.0f, 0.0f) ;
	sprite.Render() ;*/
}