#pragma once

#include "Scene.h"

class CHero ;
class CSprite ;

class SceneGravity : public Scene
{
private :
	CHero *m_pHero ;

public :
	static Scene* scene() ;

	SceneGravity() ;
	virtual ~SceneGravity() ;

	void Init() ;
	void Destroy() ;

	void Update(float dt) ;
	void Render() ;
} ;