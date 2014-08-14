#pragma once

#include "Singleton.h"
#include <vector>
#include "Objects.h"

class CTiles ;
class CDynamicObjects ;

class CMapTiles_List : public Singleton<CMapTiles_List>
{
private :
	std::vector<CTiles*> m_MapTiles_List ;

	Position m_HeroPos ;
	Size m_MapSize ;

public :
	CMapTiles_List() ;
	~CMapTiles_List() ;

	void LoadMap(int num) ;

	void Clear() ;

	const Position GetHeroPosition() ;
	const Size GetMapSize() ;
	CTiles* GetTile(int x, int y) ;
	//
	void DeleteTile(CTiles *pTile) ;
	//

	void Collision(CDynamicObjects *pObject, char coord) ;
	void Collision(char coord) ;

	const std::vector<CTiles*> GetMapTilesList() ;

	void Update() ;

	void Render() ;
} ;

#define g_MapTiles_List CMapTiles_List::GetInstance()