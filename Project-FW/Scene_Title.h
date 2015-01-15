#pragma once

#include "Scene.h"
#include <fmod.hpp>

class CSprite ;

class SceneTitle : public Scene
{
private :
	CSprite *m_pBackground ;
	CSprite *m_pButton[4] ;
	CSprite *m_pBlank ;

	int m_nMenuNum ;

	bool m_bFadeOut ;
	float m_fTime ;

	FMOD::Sound *m_pBGM ;

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
	void FadeOut() ;
} ;