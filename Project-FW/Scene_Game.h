#pragma once

#include "Scene.h"
#include <fmod.hpp>

class CHero ;
class CSprite ;
class CMapBackground ;

class SceneGame : public Scene
{
private :
	CHero *m_pHero ;
	CMapBackground *m_pMapBackground ;

	CSprite *m_pTutorial ;
	CSprite *m_pMenu, *m_pEndMenu ;
	CSprite *m_pMenuButton[3], *m_pEndMenuButton[2] ;

	float m_fTime ;

	bool m_bTutorial ;
	bool m_bMenu ;
	int m_nSelectMenuNum ;

	enum GameEndMenuState { NONE=0, MENU_IN, BUTTON_IN, SHOW } ;
	GameEndMenuState m_GameEndMenuState ;

	FMOD::Sound *m_pBGM ;

public :
	static Scene* scene() ;

	SceneGame() ;
	virtual ~SceneGame() ;

	void Init() ;
	void Destroy() ;

	void Update(float dt) ;
	void Render() ;
private :
	void Tutorial() ;
	void GameMenu() ;
	void GameEndMenu() ;
	void MenuButtonMove(CSprite **pMenuButton, const float fWidth, const float fHeight, const int nMaxMenu) ;
} ;