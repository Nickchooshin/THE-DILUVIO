#pragma once

#include "Singleton.h"
#include <vector>
#include "Objects.h"

class CTiles ;
class CDynamicObjects ;

class CMapTiles_List : public Singleton<CMapTiles_List>
{
private :
	CTiles ***m_pMapTiles_List ;	// 경계선 블럭으로 인하여, 실질적인 타일의 위치는 Index+1 의 값을 지닌다.
									// ex) 3, 8 위치의 타일 -> m_pMapTiles_List[4][9]
	Position m_HeroPos ;
	Size m_MapSize ;

public :
	CMapTiles_List() ;
	~CMapTiles_List() ;

	void LoadMap() ;

	void Clear() ;

	const Position GetHeroPosition() ;
	const Size GetMapSize() ;
	CTiles* GetTile(int x, int y) ;
	void DeleteTile(CTiles *pTile) ;
	
	std::vector<CTiles*> GetAdjacentAllMapTilesList(int x, int y, int direction, int radius=1) ;
	std::vector<CTiles*> GetAdjacentMapTilesList(int x, int y, int direction, int radius=1) ;
	std::vector<CTiles*> GetAdjacentEffectMapTilesList(int x, int y, int direction, int radius=1) ;

	void Update() ;

	void Render() ;
} ;

#define g_MapTiles_List CMapTiles_List::GetInstance()