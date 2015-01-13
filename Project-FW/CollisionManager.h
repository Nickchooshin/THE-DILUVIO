#pragma once

#include "Singleton.h"

class CCollisionManager : public Singleton<CCollisionManager>
{
public :
	CCollisionManager() ;
	~CCollisionManager() ;

	void CollisionX() ;
	void CollisionY() ;
} ;

#define g_CollisionManager CCollisionManager::GetInstance()