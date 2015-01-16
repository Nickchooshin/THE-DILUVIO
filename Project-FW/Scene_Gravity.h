#pragma once

#include "Scene.h"

class CHero ;
class CSprite ;
class CMapBackground ;

class SceneGravity : public Scene
{
private :
	CHero *m_pHero ;
	CMapBackground *m_pMapBackground ;

	CSprite *m_pMenu, *m_pEndMenu ;
	CSprite *m_pMenuButton[3], *m_pEndMenuButton[2] ;

	float m_fTime ;

	bool m_bMenu ;
	int m_nSelectMenuNum ;

	enum GameEndMenuState { NONE=0, MENU_IN, BUTTON_IN, SHOW } ;
	GameEndMenuState m_GameEndMenuState ;

public :
	static Scene* scene() ;

	SceneGravity() ;
	virtual ~SceneGravity() ;

	void Init() ;
	void Destroy() ;

	void Update(float dt) ;
	void Render() ;
private :
	void GameMenu() ;
	void GameEndMenu() ;
	void MenuButtonMove(CSprite **pMenuButton, const float fWidth, const float fHeight, const int nMaxMenu) ;
} ;