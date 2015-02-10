#pragma once

#include "Scene.h"
#include <fmod.hpp>

class CSprite ;

class SceneTitle : public Scene
{
private :
	CSprite *m_pBackground ;
	CSprite *m_pButton[4] ;
	CSprite *m_pHelp[4] ;
	CSprite *m_pConstruction ;
	CSprite *m_pBlank ;

	int m_nMenuNum ;
	int m_nHelpNum ;

	bool m_bOpenExtra ;
	bool m_bFadeOut ;
	float m_fTime ;

	int m_nKonamiCode ;

	FMOD::Sound *m_pBGM, *m_pSEButton, *m_pSECoin ;

public :
	static Scene* scene() ;

	SceneTitle() ;
	virtual ~SceneTitle() ;

	void Init() ;
	void Destroy() ;

	void Update(float dt) ;
	void Render() ;
private :
	void MenuSelect() ;
	void HelpMenu() ;
	void FadeOut() ;

	void KonamiCode() ;
} ;