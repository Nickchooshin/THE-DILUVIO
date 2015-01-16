#pragma once

#include "Scene.h"
#include <fmod.hpp>

class CSprite ;

class SceneLogo : public Scene
{
private :
	CSprite *m_pTeamLogo, *m_pTeamLogoMono ;
	CSprite *m_pGameLogo ;
	CSprite *m_pWarningLogo ;

public :
	static Scene* scene() ;

	SceneLogo() ;
	virtual ~SceneLogo() ;

	void Init() ;
	void Destroy() ;

	void Update(float dt) ;
	void Render() ;
} ;