#include "MapTiles_List.h"
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

CMapTiles_List::CMapTiles_List()
{
}
CMapTiles_List::~CMapTiles_List()
{
	Clear() ;
}

void CMapTiles_List::LoadMap(int num)
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

			CTiles *pTile=NULL ;

			switch(tileNumber)
			{
			case 0 :
				pTile = NULL ;
				break ;

			case 1 :
				pTile = NULL ;
				m_HeroPos.x = x ;
				m_HeroPos.y = y ;
				break ;

			case 2 :
				pTile = new CTiles_GroundStone ;
				break ;
			case 3 :
				pTile = new CTiles_GroundEarth ;
				break ;
			case 4 :
				pTile = new CTiles_GroundEarthUp ;
				break ;
			case 5 :
				pTile = new CTiles_GroundCreeper ;
				break ;
			case 6 :
				pTile = new CTiles_GroundWater ;
				break ;
			case 7 :
				pTile = new CTiles_GroundWaterUp ;
				break ;

			case 8 :
				pTile = new CTiles_JailTrap ;
				break ;
			case 9 :
				pTile = new CTiles_JailLever ;
				break ;

			case 10 :
				pTile = new CTiles_Glass ;
				break ;

			case 11 :
				pTile = new CTiles_Arrival ;
				break ;

			case 12 :
				pTile = new CTiles_MontriloDoor ;
				break ;

			case 13 :
				pTile = new CTiles_Spark ;
				break ;
			}

			if(pTile!=NULL)
			{
				pTile->Init() ;
				pTile->SetPosition((float)(x * 64), (float)(y * 64)) ;
				m_MapTiles_List.push_back(pTile) ;

				//
				char index[100] ;
				sprintf(index, "%d, %d", x, mapSizeY-y-1) ;
				TileList[index] = pTile ;
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

void CMapTiles_List::Clear()
{
	CTiles *temp ;
	const int size = m_MapTiles_List.size() ;

	for(int i=0; i<size; i++)
	{
		temp = m_MapTiles_List[i] ;
		delete temp ;
	}

	if(!m_MapTiles_List.empty())
		m_MapTiles_List.clear() ;
}

const Position CMapTiles_List::GetHeroPosition()
{
	return m_HeroPos ;
}

const Size CMapTiles_List::GetMapSize()
{
	return m_MapSize ;
}

CTiles* CMapTiles_List::GetTile(int x, int y)
{
	CTiles *pTile ;
	const int size = m_MapTiles_List.size() ;

	float fX, fY ;
	float fTileX, fTileY ;
	fX = (float)x * 64.0f ;
	fY = (float)y * 64.0f ;

	for(int i=0; i<size; i++)
	{
		pTile = m_MapTiles_List[i] ;

		fTileX = pTile->GetPositionX() ;
		fTileY = pTile->GetPositionY() ;

		//if(pTile->BeCollision() && (fTileX==fX && fTileY==fY))
		if((pTile->BeCollision() || !pTile->BeNonCollision(NULL)) && (fTileX==fX && fTileY==fY))
			return pTile ;
	}

	return NULL ;
}

//
void CMapTiles_List::DeleteTile(CTiles *pTile)
{
	CTiles *pTemp ;
	const int size = m_MapTiles_List.size() ;

	for(int i=0; i<size; i++)
	{
		pTemp = m_MapTiles_List[i] ;

		if(pTemp==pTile)
		{
			delete pTemp ;
			m_MapTiles_List.erase( m_MapTiles_List.begin() + i ) ;
			break ;
		}
	}
}
//

/*void CMapTiles_List::Collision(CDynamicObjects *pDynamicObject, char coord)
{
	CCollision col ;

	CTiles *pTile ;
	const int size = m_MapTiles_List.size() ;

	for(int i=0; i<size; i++)
	{
		pTile = m_MapTiles_List[i] ;

		if(coord=='x' || coord=='X')
			col.XCollision(pDynamicObject, pTile) ;
		else if(coord=='y' || coord=='Y')
			col.YCollision(pDynamicObject, pTile) ;
	}
}

void CMapTiles_List::Collision(char coord)
{
	CCollision col ;

	CDynamicObjects *pDynamicObject ;
	CTiles *pTile ;
	std::vector<CDynamicObjects*> DynamicObjects_List = g_DynamicObjects_List->GetDynamicObjectsList() ;
	const int ObjectSize = DynamicObjects_List.size() ;
	const int TileSize = m_MapTiles_List.size() ;

	for(int Index_o=0; Index_o<ObjectSize; Index_o++)
	{
		pDynamicObject = DynamicObjects_List[Index_o] ;
		//BeGravityMultiples = false ;
		//
		pDynamicObject->SetGravityMultiples(1.0f) ;
		pDynamicObject->SetMultipleJump(false) ;

		for(int Index_t=0; Index_t<TileSize; Index_t++)
		{
			pTile = m_MapTiles_List[Index_t] ;
			bool bCollision=false ;

			if(coord=='x' || coord=='X')
				bCollision = col.XCollision(pDynamicObject, pTile) ;
			else if(coord=='y' || coord=='Y')
				bCollision = col.YCollision(pDynamicObject, pTile) ;

			//if(bCollision && pTile->BeGravityMultiples())
			//	BeGravityMultiples = true ;
		}

		//if(!BeGravityMultiples)
		//	pDynamicObject->SetGravityMultiples(1.0f) ;
	}
}*/

const std::vector<CTiles*> CMapTiles_List::GetMapTilesList()
{
	return m_MapTiles_List ;
}

void CMapTiles_List::Update()
{
	CTiles *pTile ;
	const int size = m_MapTiles_List.size() ;

	for(int i=0; i<size; i++)
	{
		pTile = m_MapTiles_List[i] ;
		pTile->Update() ;
	}
}

void CMapTiles_List::Render()
{
	CTiles *pTile ;
	const int size = m_MapTiles_List.size() ;

	for(int i=0; i<size; i++)
	{
		pTile = m_MapTiles_List[i] ;
		pTile->Render() ;
	}
}