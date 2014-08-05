#pragma once

#include <vector>
#include "Objects.h"

class CTiles ;
class CDynamicObjects ;

class CMapTiles
{
private :
	std::vector<CTiles*> m_Tiles ;

	Position m_HeroPos ;
	Size m_MapSize ;

public :
	CMapTiles() ;
	~CMapTiles() ;

	void LoadMap(int num) ;

	void Clear() ;

	const Position GetHeroPosition() ;
	const Size GetMapSize() ;
	CTiles* GetTile(int x, int y) ;

	void Collision(CDynamicObjects *pObjects, char coord) ;
	void Collision(char coord) ;

	void Update() ;

	void Render() ;
} ;