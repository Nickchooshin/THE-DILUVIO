#include "MapTiles.h"
#include "Tiles.h"
#include "DynamicObjects.h"
#include "Collision.h"

#include "Tiles_Ground.h"

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
		for(int x=mapSizeX-1; x>=0; x--)
		{
			fscanf(map, "%d ", &tileNumber) ;

			CTiles *pTiles=NULL ;

			switch(tileNumber)
			{
			case 0 :
				pTiles = NULL ;
				break ;

			case 1 :
			case 2 :
				pTiles = new CTilesGround ;
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
}

void CMapTiles::Clear()
{
	CTiles* temp ;
	std::vector<CTiles*>::iterator iter ;
	std::vector<CTiles*>::iterator end=m_Tiles.end() ;

	for(iter=m_Tiles.begin(); iter!=end; iter++)
	{
		temp = *iter ;
		delete temp ;
	}

	m_Tiles.clear() ;
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

	CTiles* temp ;
	std::vector<CTiles*>::iterator iter ;
	std::vector<CTiles*>::iterator end=m_Tiles.end() ;

	for(iter=m_Tiles.begin(); iter!=end; iter++)
	{
		temp = *iter ;

		if(coord=='x' || coord=='X')
			col.XCollision(pObjects, temp) ;
		else if(coord=='y' || coord=='Y')
			col.YCollision(pObjects, temp) ;
	}
}

void CMapTiles::Collision(char coord)
{
	CCollision col ;

	CDynamicObjects *pObject ;
	CTiles *pTile ;
	std::vector<CTiles*>::iterator iter_t, end_t=m_Tiles.end() ;
	std::vector<CDynamicObjects*>::iterator iter_o, end_o=m_CollisionList.end() ;

	for(iter_t=m_Tiles.begin(); iter_t!=end_t; iter_t++)
	{
		pTile = *iter_t ;

		for(iter_o=m_CollisionList.begin(); iter_o!=end_o; iter_o++)
		{
			pObject = *iter_o ;

			if(coord=='x' || coord=='X')
				col.XCollision(pObject, pTile) ;
			else if(coord=='y' || coord=='Y')
				col.YCollision(pObject, pTile) ;
		}
	}
}

void CMapTiles::Render()
{
	CTiles* temp ;
	std::vector<CTiles*>::iterator iter ;
	std::vector<CTiles*>::iterator end=m_Tiles.end() ;

	for(iter=m_Tiles.begin(); iter!=end; iter++)
	{
		temp = *iter ;
		temp->Render() ;
	}
}