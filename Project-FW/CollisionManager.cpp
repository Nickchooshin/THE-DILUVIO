#include "CollisionManager.h"
#include "Collision.h"
#include "DynamicObjects_List.h"
#include "MapTiles_List.h"

#include "DynamicObjects.h"

#include <algorithm>

CCollisionManager::CCollisionManager()
{
}
CCollisionManager::~CCollisionManager()
{
}

void CCollisionManager::CollisionX()
{
	CCollision col ;
	
	CDynamicObjects *pDynamicObject ;
	CTiles *pTile ;
	std::vector<CDynamicObjects*> DynamicObjects_List = g_DynamicObjects_List->GetDynamicObjectsList() ;
	std::vector<CTiles*> MapTiles_List ;
	const int ObjectSize = DynamicObjects_List.size() ;
	int TileSize ;

	for(int Index_o=0; Index_o<ObjectSize; Index_o++)
	{
		pDynamicObject = DynamicObjects_List[Index_o] ;
		pDynamicObject->SetGravityMultiples(1.0f) ;
		pDynamicObject->SetMultipleJump(false) ;

		//********** MapTiles_List Collision (NonEffect) **********//
		const int x = (int)(pDynamicObject->GetPositionX() / 64.0f) ;
		const int y = (int)(pDynamicObject->GetPositionY() / 64.0f) ;

		MapTiles_List = g_MapTiles_List->GetAdjacentMapTilesList(x, y) ;
		TileSize = MapTiles_List.size() ;

		for(int Index_t=0; Index_t<TileSize; Index_t++)
		{
			pTile = MapTiles_List[Index_t] ;
			bool bCollision=false ;

			bCollision = col.XCollision(pDynamicObject, pTile) ;
		}

		//********** DynamicObjects_List Collision **********//
		if(pDynamicObject==g_DynamicObjects_List->GetMainChar())
			continue ;

		for(int Index_o2=0; Index_o2<ObjectSize; Index_o2++)
		{
			if(Index_o==Index_o2)
				continue ;

			col.XCollision(DynamicObjects_List[Index_o2], DynamicObjects_List[Index_o]) ;
		}
	}

	for(int Index_o=0; Index_o<ObjectSize; Index_o++)
	{
		pDynamicObject = DynamicObjects_List[Index_o] ;

		//********** MapTiles_List Collision (NonEffect) **********//
		const int x = (int)(pDynamicObject->GetPositionX() / 64.0f) ;
		const int y = (int)(pDynamicObject->GetPositionY() / 64.0f) ;

		MapTiles_List = g_MapTiles_List->GetAdjacentEffectMapTilesList(x, y) ;
		TileSize = MapTiles_List.size() ;

		for(int Index_t=0; Index_t<TileSize; Index_t++)
		{
			pTile = MapTiles_List[Index_t] ;
			bool bCollision=false ;

			bCollision = col.XCollision(pDynamicObject, pTile) ;
		}
	}
}

void CCollisionManager::CollisionY()
{
	CCollision col ;
	
	CDynamicObjects *pDynamicObject ;
	CTiles *pTile ;
	std::vector<CDynamicObjects*> DynamicObjects_List = g_DynamicObjects_List->GetDynamicObjectsList() ;
	std::vector<CTiles*> MapTiles_List ;
	const int ObjectSize = DynamicObjects_List.size() ;
	int TileSize ;

	std::sort(DynamicObjects_List.begin(), DynamicObjects_List.end(), CObjects::collision_priority) ;

	for(int Index_o=0; Index_o<ObjectSize; Index_o++)
	{
		pDynamicObject = DynamicObjects_List[Index_o] ;
		//BeGravityMultiples = false ;
		//
		pDynamicObject->SetGravityMultiples(1.0f) ;
		pDynamicObject->SetMultipleJump(false) ;

		//********** MapTiles_List Collision **********//
		const int x = (int)(pDynamicObject->GetPositionX() / 64.0f) ;
		const int y = (int)(pDynamicObject->GetPositionY() / 64.0f) ;

		MapTiles_List = g_MapTiles_List->GetAdjacentAllMapTilesList(x, y) ;
		TileSize = MapTiles_List.size() ;

		for(int Index_t=0; Index_t<TileSize; Index_t++)
		{
			pTile = MapTiles_List[Index_t] ;
			bool bCollision=false ;

			bCollision = col.YCollision(pDynamicObject, pTile) ;

			//if(bCollision && pTile->BeGravityMultiples())
			//	BeGravityMultiples = true ;
		}

		//if(!BeGravityMultiples)
		//	pDynamicObject->SetGravityMultiples(1.0f) ;

		//********** DynamicObjects_List Collision **********//
		if(pDynamicObject==g_DynamicObjects_List->GetMainChar())
			continue ;

		for(int Index_o2=0; Index_o2<ObjectSize; Index_o2++)
		{
			if(Index_o==Index_o2)
				continue ;

			col.YCollision(DynamicObjects_List[Index_o2], DynamicObjects_List[Index_o]) ;
		}
	}
}