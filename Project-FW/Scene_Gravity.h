#pragma once

#include "Scene.h"

class CHero ;
class CMapTiles ;
class CCollision ;
class CSprite ;

class SceneGravity : public Scene
{
private :
	CHero *m_pHero ;
	CMapTiles *m_MapTiles ;
	CCollision *m_pCollision ;

public :
	static Scene* scene() ;

	SceneGravity() ;
	virtual ~SceneGravity() ;

	void Init() ;
	void Destroy() ;

	void Update(float dt) ;
	void Render() ;
} ;