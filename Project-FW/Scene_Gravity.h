#pragma once

#include "Scene.h"

class CHero ;
class CTilesGround ;
class CCrashChecker ;

class SceneGravity : public Scene
{
private :
	CHero *m_pHero ;
	CTilesGround *m_pTile ;
	CCrashChecker *m_pCrash ;

public :
	static Scene* scene() ;

	SceneGravity() ;
	virtual ~SceneGravity() ;

	void Init() ;
	void Destroy() ;

	void Update(float dt) ;
	void Render() ;
} ;