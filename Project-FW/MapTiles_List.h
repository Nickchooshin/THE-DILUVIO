#pragma once

#include "Singleton.h"
#include <vector>
#include "Objects.h"

class CTiles ;
class CDynamicObjects ;

class CMapTiles_List : public Singleton<CMapTiles_List>
{
private :
	CTiles ***m_pMapTiles_List ;

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

	std::vector<CTiles*> GetAdjacentMapTilesList(int x, int y, int radius=1) ;

	void Update() ;

	void Render() ;
} ;

#define g_MapTiles_List CMapTiles_List::GetInstance()