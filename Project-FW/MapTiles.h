#pragma once

#include <vector>

class CTiles ;
class CDynamicObjects ;

class CMapTiles
{
private :
	std::vector<CTiles*> m_Tiles ;
	std::vector<CDynamicObjects*> m_CollisionList ;

public :
	CMapTiles() ;
	~CMapTiles() ;

	void LoadMap(int num) ;

	void Clear() ;

	CTiles* GetTile(int x, int y) ;

	void AddCollisionList(CDynamicObjects *pObjects) ;
	void ClearCollisionList() ;
	void Collision(CDynamicObjects *pObjects, char coord) ;
	void Collision(char coord) ;

	void Render() ;
} ;