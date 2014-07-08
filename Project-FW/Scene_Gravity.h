#pragma once

#include "Scene.h"

class CHero ;
class CTilesGround ;
class CCollision ;
class CSprite ;

class SceneGravity : public Scene
{
private :
	CHero *m_pHero ;
	CTilesGround *m_pTiles[5] ;
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