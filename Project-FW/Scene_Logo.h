#pragma once

#include "Scene.h"
#include <fmod.hpp>

class CSprite ;

class SceneLogo : public Scene
{
private :
	CSprite *m_pBlank ;
	CSprite *m_pTeamLogo, *m_pTeamLogoMono ;
	CSprite *m_pGameLogo ;
	CSprite *m_pWarningLogo ;
	
	FMOD::Sound *m_pBGM ;

	float m_fTime ;

	enum LogoState { TEAMLOGOMONO_IN=0, TEAMLOGO_IN, TEAMLOGO, TEAMLOGO_OUT, TEAMLOGOMONO_OUT,
					 GAMELOGO_IN, GAMELOGO, GAMELOGO_OUT,
					 WARNINGLOGO_IN, WARNINGLOGO, WARNINGLOGO_OUT } ;

	LogoState m_LogoState ;

public :
	static Scene* scene() ;

	SceneLogo() ;
	virtual ~SceneLogo() ;

	void Init() ;
	void Destroy() ;

	void Update(float dt) ;
	void Render() ;
} ;