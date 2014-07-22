#include "MapTiles.h"
#include "Tiles.h"
#include "DynamicObjects.h"
#include "Collision.h"

#include "Tiles_GroundStone.h"
#include "Tiles_GroundEarth.h"
#include "Tiles_GroundEarthUp.h"
#include "Tiles_GroundCreeper.h"
#include "Tiles_GroundWater.h"
#include "Tiles_GroundWaterUp.h"
#include "Tiles_JailTrap.h"
#include "Tiles_JailButton.h"
#include "Tiles_Glass.h"
#include "Tiles_Arrival.h"
#include "Tiles_MontriloDoor.h"

#include <string>

CMapTiles::CMapTiles()
{
}
CMapTiles::~CMapTiles()
{
	Clear() ;
}

void CMapTiles::LoadMap(int num)
{
	FILE *map ;
	char filepath[100] ;
	int mapSizeX, mapSizeY ;
	int tileNumber ;

	sprintf_s(filepath, "Resource/Data/Maps/%d.dat", num) ;

	map = fopen(filepath, "r") ;

	fscanf(map, "%d %d\n", &mapSizeX, &mapSizeY) ;

	for(int y=mapSizeY-1; y>=0; y--)
	{
		for(int x=0; x<mapSizeX; x++)
		{
			fscanf(map, "%d ", &tileNumber) ;

			CTiles *pTiles=NULL ;

			switch(tileNumber)
			{
			case 0 :
				pTiles = NULL ;
				break ;

			case 1 :
				pTiles = NULL ;
				m_HeroPos.x = x ;
				m_HeroPos.y = y ;
				break ;

			case 2 :
				pTiles = new CTiles_GroundStone ;
				break ;
			case 3 :
				pTiles = new CTiles_GroundEarth ;
				break ;
			case 4 :
				pTiles = new CTiles_GroundEarthUp ;
				break ;
			case 5 :
				pTiles = new CTiles_GroundCreeper ;
				break ;
			case 6 :
				pTiles = new CTiles_GroundWater ;
				break ;
			case 7 :
				pTiles = new CTiles_GroundWaterUp ;
				break ;

			case 8 :
				pTiles = new CTiles_JailTrap ;
				break ;
			case 9 :
				pTiles = new CTiles_JailButton ;
				break ;

			case 10 :
				pTiles = new CTiles_Glass ;
				break ;

			case 11 :
				pTiles = new CTiles_Arrival ;
				break ;

			case 12 :
				pTiles = new CTiles_MontriloDoor ;
				break ;
			}

			if(pTiles!=NULL)
			{
				pTiles->Init() ;
				pTiles->SetPosition((float)(x * 64 + 32), (float)(y * 64 + 32)) ;
				m_Tiles.push_back(pTiles) ;
			}
		}
	}

	fclose(map) ;

	m_MapSize.x = mapSizeX ;
	m_MapSize.y = mapSizeY ;
}

void CMapTiles::Clear()
{
	CTiles *temp ;
	std::vector<CTiles*>::iterator iter ;
	std::vector<CTiles*>::iterator end=m_Tiles.end() ;

	for(iter=m_Tiles.begin(); iter!=end; iter++)
	{
		temp = *iter ;
		delete temp ;
	}

	m_Tiles.clear() ;
}

const Position CMapTiles::GetHeroPosition()
{
	return m_HeroPos ;
}

const Size CMapTiles::GetMapSize()
{
	return m_MapSize ;
}

CTiles* CMapTiles::GetTile(int x, int y)
{
	CTiles *pTiles ;
	std::vector<CTiles*>::iterator iter ;
	std::vector<CTiles*>::iterator end=m_Tiles.end() ;

	float fX, fY ;
	float fTileX, fTileY ;
	fX = (float)(x-1) * 64.0f + 32.0f ;
	fY = (float)(y-1) * 64.0f + 32.0f ;

	for(iter=m_Tiles.begin(); iter!=end; iter++)
	{
		pTiles = *iter ;

		fTileX = pTiles->GetPositionX() ;
		fTileY = pTiles->GetPositionY() ;

		if(fTileX==fX && fTileY==fY)
			return pTiles ;
	}

	return NULL ;
}

void CMapTiles::AddCollisionList(CDynamicObjects *pObjects)
{
	m_CollisionList.push_back(pObjects) ;
}

void CMapTiles::ClearCollisionList()
{
	m_CollisionList.clear() ;
}

void CMapTiles::Collision(CDynamicObjects *pObjects, char coord)
{
	CCollision col ;

	CTiles *pTiles ;
	std::vector<CTiles*>::iterator iter ;
	std::vector<CTiles*>::iterator end=m_Tiles.end() ;

	for(iter=m_Tiles.begin(); iter!=end; iter++)
	{
		pTiles = *iter ;

		if(coord=='x' || coord=='X')
			col.XCollision(pObjects, pTiles) ;
		else if(coord=='y' || coord=='Y')
			col.YCollision(pObjects, pTiles) ;
	}
}

void CMapTiles::Collision(char coord)
{
	CCollision col ;

	CDynamicObjects *pObject ;
	CTiles *pTiles ;
	std::vector<CTiles*>::iterator iter_t, end_t=m_Tiles.end() ;
	std::vector<CDynamicObjects*>::iterator iter_o, end_o=m_CollisionList.end() ;

	for(iter_t=m_Tiles.begin(); iter_t!=end_t; iter_t++)
	{
		pTiles = *iter_t ;

		for(iter_o=m_CollisionList.begin(); iter_o!=end_o; iter_o++)
		{
			pObject = *iter_o ;

			if(coord=='x' || coord=='X')
				col.XCollision(pObject, pTiles) ;
			else if(coord=='y' || coord=='Y')
				col.YCollision(pObject, pTiles) ;
		}
	}
}

void CMapTiles::Update()
{
	CTiles *pTiles ;
	std::vector<CTiles*>::iterator iter ;
	std::vector<CTiles*>::iterator end=m_Tiles.end() ;

	for(iter=m_Tiles.begin(); iter!=end; iter++)
	{
		pTiles = *iter ;
		pTiles->Update() ;
	}
}

void CMapTiles::Render()
{
	CTiles *pTiles ;
	std::vector<CTiles*>::iterator iter ;
	std::vector<CTiles*>::iterator end=m_Tiles.end() ;

	for(iter=m_Tiles.begin(); iter!=end; iter++)
	{
		pTiles = *iter ;
		pTiles->Render() ;
	}
}