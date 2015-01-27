#pragma once

#include "Scene.h"
#include <fmod.hpp>

class CSprite ;

class SceneCredit : public Scene
{
private :
	CSprite *m_pBackground, *m_pCredit ;
	CSprite *m_pBlank ;

	bool m_bFadeOut ;
	float m_fTime, m_fFadeOut ;

	FMOD::Sound *m_pBGM ;

public :
	static Scene* scene() ;

	SceneCredit() ;
	virtual ~SceneCredit() ;

	void Init() ;
	void Destroy() ;

	void Update(float dt) ;
	void Render() ;
} ;