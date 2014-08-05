#include "MapTiles.h"
#include "Tiles.h"
#include "DynamicObjects.h"
#include "Collision.h"

#include "DynamicObjects_List.h"

#include "Tiles_GroundStone.h"
#include "Tiles_GroundEarth.h"
#include "Tiles_GroundEarthUp.h"
#include "Tiles_GroundCreeper.h"
#include "Tiles_GroundWater.h"
#include "Tiles_GroundWaterUp.h"
#include "Tiles_JailTrap.h"
#include "Tiles_JailLever.h"
#include "Tiles_Glass.h"
#include "Tiles_Arrival.h"
#include "Tiles_MontriloDoor.h"
#include "Tiles_Spark.h"

#include <string>
#include <map>

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

	//
	std::map<std::string, CTiles*> TileList ;
	//

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
				pTiles = new CTiles_JailLever ;
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

			case 13 :
				pTiles = new CTiles_Spark ;
				break ;
			}

			if(pTiles!=NULL)
			{
				pTiles->Init() ;
				pTiles->SetPosition((float)(x * 64), (float)(y * 64)) ;
				m_Tiles.push_back(pTiles) ;

				//
				char index[100] ;
				sprintf(index, "%d, %d", x, mapSizeY-y-1) ;
				TileList[index] = pTiles ;
				//
			}
		}
	}

	fclose(map) ;

	//
	sprintf_s(filepath, "Resource/Data/Maps/%d.link", num) ;

	map = fopen(filepath, "r") ;
	if(map!=NULL)
	{
		int LinkNum ;

		fscanf(map, "%d\n", &LinkNum) ;

		for(int i=0; i<LinkNum; i++)
		{
			int LinkX, LinkY ;
			int LinkedX, LinkedY ;
			char LinkIndex[100], LinkedIndex[100] ;

			fscanf(map, "%d %d\t%d %d\n", &LinkX, &LinkY, &LinkedX, &LinkedY) ;

			sprintf(LinkIndex, "%d, %d", LinkX, LinkY) ;
			sprintf(LinkedIndex, "%d, %d", LinkedX, LinkedY) ;

			CTiles *pLinkTile = TileList[LinkIndex] ;
			CTiles *pLinkedTile = TileList[LinkedIndex] ;
			pLinkTile->SetLinkedTile(pLinkedTile) ;
		}

		fclose(map) ;
	}
	//

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
		temp = (*iter) ;
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
	fX = (float)x * 64.0f ;
	fY = (float)y * 64.0f ;

	for(iter=m_Tiles.begin(); iter!=end; iter++)
	{
		pTiles = (*iter) ;

		fTileX = pTiles->GetPositionX() ;
		fTileY = pTiles->GetPositionY() ;

		if(pTiles->BeCollision() && (fTileX==fX && fTileY==fY))
			return pTiles ;
	}

	return NULL ;
}

void CMapTiles::Collision(CDynamicObjects *pObjects, char coord)
{
	CCollision col ;

	CTiles *pTiles ;
	std::vector<CTiles*>::iterator iter ;
	std::vector<CTiles*>::iterator end=m_Tiles.end() ;

	for(iter=m_Tiles.begin(); iter!=end; iter++)
	{
		pTiles = (*iter) ;

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
	std::vector<CDynamicObjects*> DynamicObjects_List = g_DynamicObjects_List->GetDynamicObjectsList() ;
	const int ObjectSize = DynamicObjects_List.size() ;
	const int TileSize = m_Tiles.size() ;

	bool BeGravityMultiples ;

	for(int Index_o=0; Index_o<ObjectSize; Index_o++)
	{
		pObject = DynamicObjects_List[Index_o] ;
		BeGravityMultiples = false ;

		for(int Index_t=0; Index_t<TileSize; Index_t++)
		{
			pTiles = m_Tiles[Index_t] ;
			bool bCollision=false ;

			if(coord=='x' || coord=='X')
				bCollision = col.XCollision(pObject, pTiles) ;
			else if(coord=='y' || coord=='Y')
				bCollision = col.YCollision(pObject, pTiles) ;

			if(bCollision && pTiles->BeGravityMultiples())
				BeGravityMultiples = true ;
		}

		if(!BeGravityMultiples)
			pObject->SetGravityMultiples(1.0f) ;
	}
}

void CMapTiles::Update()
{
	CTiles *pTiles ;
	std::vector<CTiles*>::iterator iter ;
	std::vector<CTiles*>::iterator end=m_Tiles.end() ;

	for(iter=m_Tiles.begin(); iter!=end; iter++)
	{
		pTiles = (*iter) ;
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
		pTiles = (*iter) ;
		pTiles->Render() ;
	}
}