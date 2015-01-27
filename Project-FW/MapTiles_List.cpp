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

#include "StageProgress.h"

#include <string>
#include <map>

CMapTiles_List::CMapTiles_List() : m_pMapTiles_List(NULL)
{
}
CMapTiles_List::~CMapTiles_List()
{
	Clear() ;
}

void CMapTiles_List::LoadMap()
{
	FILE *map ;
	char filepath[100] ;
	int mapSizeX, mapSizeY ;
	int tileNumber ;
	bool bBoaderLineX=false ;

	// Map dat 파일 불러오기
	sprintf_s(filepath, "Resource/Data/Maps/%s.dat", g_StageProgress->GetSelectMapName()) ;

	map = fopen(filepath, "r") ;

	fscanf(map, "%d %d\n", &mapSizeX, &mapSizeY) ;

	m_pMapTiles_List = new CTiles**[mapSizeX+2] ;
	for(int i=0; i<mapSizeX+2; i++)
	{
		m_pMapTiles_List[i] = new CTiles*[mapSizeY+2] ;

		for(int j=0; j<mapSizeY+2; j++)
			m_pMapTiles_List[i][j] = NULL ;
	}

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
				m_pMapTiles_List[x+1][y+1] = &(*pTile) ;
			}

			// 맵 밖으로 나가지 못하게 하기 위한, 경계선 블럭 X축
			if(!bBoaderLineX)
			{
				CTiles *pTile ;
				
				pTile = new CTiles_GroundStone ;
				pTile->Init() ;
				pTile->SetPosition((float)(x * 64), -64.0f) ;
				m_pMapTiles_List[x+1][0] = &(*pTile) ;
		
				pTile = new CTiles_GroundStone ;
				pTile->Init() ;
				pTile->SetPosition((float)(x * 64), (float)(mapSizeY * 64)) ;
				m_pMapTiles_List[x+1][mapSizeY+1] = &(*pTile) ;
			}
		}

		// 맵 밖으로 나가지 못하게 하기 위한, 경계선 블럭 Y축
		CTiles *pTile ;

		pTile = new CTiles_GroundStone ;
		pTile->Init() ;
		pTile->SetPosition(-64.0f, (float)(y * 64)) ;
		m_pMapTiles_List[0][y+1] = &(*pTile) ;
		
		pTile = new CTiles_GroundStone ;
		pTile->Init() ;
		pTile->SetPosition((float)(mapSizeX * 64), (float)(y * 64)) ;
		m_pMapTiles_List[mapSizeX+1][y+1] = &(*pTile) ;

		bBoaderLineX = true ;
	}

	fclose(map) ;

	// Map Link 파일 불러오기
	sprintf_s(filepath, "Resource/Data/Maps/%s.link", g_StageProgress->GetSelectMapName()) ;

	map = fopen(filepath, "r") ;
	if(map!=NULL)
	{
		int LinkNum ;

		fscanf(map, "%d\n", &LinkNum) ;

		for(int i=0; i<LinkNum; i++)
		{
			int LinkX, LinkY ;
			int LinkedX, LinkedY ;

			fscanf(map, "%d %d\t%d %d\n", &LinkX, &LinkY, &LinkedX, &LinkedY) ;

			LinkY = (mapSizeY-1) - LinkY ;
			LinkedY = (mapSizeY-1) - LinkedY ;

			CTiles *pLinkTile = m_pMapTiles_List[LinkX+1][LinkY+1] ;
			CTiles *pLinkedTile = m_pMapTiles_List[LinkedX+1][LinkedY+1] ;
		}

		fclose(map) ;
	}

	m_MapSize.x = mapSizeX ;
	m_MapSize.y = mapSizeY ;
}

void CMapTiles_List::Clear()
{
	if(m_pMapTiles_List==NULL)
		return ;

	for(int x=0; x<m_MapSize.x+2; x++)
	{
		for(int y=0; y<m_MapSize.y+2; y++)
		{
			if(m_pMapTiles_List[x][y]!=NULL)
			{
				delete m_pMapTiles_List[x][y] ;
				m_pMapTiles_List[x][y] = NULL ;
			}
		}

		delete[] m_pMapTiles_List[x] ;
		m_pMapTiles_List[x] = NULL ;
	}

	delete[] m_pMapTiles_List ;
	m_pMapTiles_List = NULL ;
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
	CTiles *pTile = m_pMapTiles_List[x+1][y+1] ;
	
	if(pTile!=NULL && (pTile->BeCollision() || !pTile->BeNonCollision(NULL)))
		return pTile ;

	return NULL ;
}

void CMapTiles_List::DeleteTile(CTiles *pTile)
{
	const int x = (int)(pTile->GetPositionX() / 64.0f) ;
	const int y = (int)(pTile->GetPositionY() / 64.0f) ;

	delete m_pMapTiles_List[x+1][y+1] ;
	m_pMapTiles_List[x+1][y+1] = NULL ;
}

std::vector<CTiles*> CMapTiles_List::GetAdjacentMapTilesList(int x, int y, int radius)
{
	std::vector<CTiles*> MapTiles ;

	for(int i=x-radius; i<=x+radius; i++)
	{
		for(int j=y-radius; j<=y+radius; j++)
		{
			if((i>=-1 && i<=m_MapSize.x) && (j>=-1 && j<=m_MapSize.y))
			{
				if(m_pMapTiles_List[i+1][j+1]!=NULL)
					MapTiles.push_back(m_pMapTiles_List[i+1][j+1]) ;
			}
		}
	}

	return MapTiles ;
}

void CMapTiles_List::Update()
{
	CTiles *pTile ;

	for(int x=0; x<m_MapSize.x+2; x++)
	{
		for(int y=0; y<m_MapSize.y+2; y++)
		{
			pTile = m_pMapTiles_List[x][y] ;
			if(pTile!=NULL)
			{
				pTile->Update() ;
				pTile->EventClear() ;
			}
		}
	}
}

void CMapTiles_List::Render()
{
	CTiles *pTile ;

	for(int x=0; x<m_MapSize.x; x++)
	{
		for(int y=0; y<m_MapSize.y; y++)
		{
			pTile = m_pMapTiles_List[x+1][y+1] ;
			if(pTile!=NULL)
				pTile->Render() ;
		}
	}
}