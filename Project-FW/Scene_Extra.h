#pragma once

#include "Scene.h"
#include <fmod.hpp>

class CSprite ;

class SceneExtra : public Scene
{
private :
	CSprite *m_pBackground ;

public :
	static Scene* scene() ;

	SceneExtra() ;
	virtual ~SceneExtra() ;

	void Init() ;
	void Destroy() ;

	void Update(float dt) ;
	void Render() ;
} ;