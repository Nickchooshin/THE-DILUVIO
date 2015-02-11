#pragma once

#include "Scene.h"
#include <fmod.hpp>

class CSprite ;

class SceneExtraStageSelect : public Scene
{
private :
	const float m_fWinWidth, m_fWinHeight ;

	CSprite *m_pBackground ;
	CSprite *m_pStageFrame, *m_pStageNameFrame ;
	CSprite *m_pProgress[9], *m_pPlayer, *m_pCastle, *m_pTile ;
	CSprite *m_pPrev, *m_pNext ;
	CSprite *m_pStageNumber, *m_pStageName ;
	CSprite **m_pStagePreview_List ;

	bool m_bPressPrev, m_bPressNext ;

	float m_fFlagAnimationTime, m_fPlayerAnimationTime ;
	int m_nFlagFrame, m_nPlayerFrame ;

	FMOD::Sound *m_pBGM ;

public :
	static Scene* scene() ;

	SceneExtraStageSelect() ;
	virtual ~SceneExtraStageSelect() ;

	void Init() ;
	void Destroy() ;

	void Update(float dt) ;
	void Render() ;
private :
	void StageSelect() ;

	void FlagAnimation() ;
	void PlayerAnimation() ;
} ;