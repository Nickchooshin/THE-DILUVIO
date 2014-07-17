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
	int i, j ;
	int size = g_Friends_List->GetSize() ;

	m_MapTiles->ClearCollisionList() ;
	m_MapTiles->AddCollisionList(m_pHero) ;
	for(int i=0; i<size; i++)
	{
		CFriends *pFriend = g_Friends_List->GetFriend(i) ;
		if(pFriend->GetRelease())
			m_MapTiles->AddCollisionList(pFriend) ;
	}

	m_MapTiles->Collision('x') ;
	///
	CCollision col ;
	for(i=0; i<size; i++)
	{
		CFriends *pFriend1 = g_Friends_List->GetFriend(i) ;
		if(!pFriend1->GetRelease())
			continue ;
		//col.XCollision(m_pHero, pFriend1) ;

		for(j=0; j<size; j++)
		{
			if(i==j)
				continue ;

			CFriends *pFriend2 = g_Friends_List->GetFriend(j) ;
			if(!pFriend2->GetRelease())
				continue ;
			col.XCollision(pFriend1, pFriend2) ;
		}
		col.XCollision(m_pHero, pFriend1) ;
	}
	///

	m_pHero->Gravity() ;
	g_Friends_List->Gravity() ;

	m_MapTiles->Collision('y') ;
	///
	g_Friends_List->Collision() ;
	for(i=0; i<size; i++)
	{
		CFriends *pFriend1 = g_Friends_List->GetFriend(i) ;
		if(!pFriend1->GetRelease())
			continue ;
		//col.YCollision(m_pHero, pFriend1) ;

		/*for(j=0; j<size; j++)
		{
			if(i==j)
				continue ;

			CFriends *pFriend2 = g_Friends_List->GetFriend(j) ;
			if(!pFriend2->GetRelease())
				continue ;
			col.YCollision(pFriend1, pFriend2) ;
		}*/
		col.YCollision(m_pHero, pFriend1) ;
	}
	///
	//

	/*m_MapTiles->Collision(m_pHero, 'x') ;
	int size = g_Friends_List->GetSize() ;
	CFriends *pFriends ;
	for(int i=0; i<size; i++)
	{
		pFriends = g_Friends_List->GetFriend(i) ;
		if(pFriends->GetRelease())
		{
			m_MapTiles->Collision(pFriends, 'x') ;
			CCollision col ;
			col.XCollision(m_pHero, pFriends) ;
		}
	}

	m_pHero->Gravity() ;
	g_Friends_List->Gravity() ;

	m_MapTiles->Collision(m_pHero, 'y') ;
	for(int i=0; i<size; i++)
	{
		pFriends = g_Friends_List->GetFriend(i) ;
		if(pFriends->GetRelease())
		{
			m_MapTiles->Collision(pFriends, 'y') ;
			CCollision col ;
			col.YCollision(m_pHero, pFriends) ;
		}
	}*/
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