#pragma once

#include "Scene.h"

class CHero ;
class CTilesGround ;
class CSampleFriend ;
class CCollision ;
class CSprite ;

class CFriendChange_UI ;

class SceneGravity : public Scene
{
private :
	CHero *m_pHero ;
	CTilesGround *m_pTiles[5] ;
	CSampleFriend *m_pFriend ;
	CCollision *m_pCollision ;

	CFriendChange_UI *m_pFC_UI ;

public :
	static Scene* scene() ;

	SceneGravity() ;
	virtual ~SceneGravity() ;

	void Init() ;
	void Destroy() ;

	void Update(float dt) ;
	void Render() ;
} ;