#pragma once

#include "Scene.h"
#include <vector>
#include <fmod.hpp>

class CSprite ;
class CScrollBackground ;

class SceneStageSelect : public Scene
{
private :
	const float m_fWinWidth, m_fWinHeight ;

	CScrollBackground *m_pBackground ;
	CSprite *m_pBackground_Brick, *m_pStageFrame, *m_pStageNameFrame ;
	CSprite *m_pProgress[5], *m_pPlayer, *m_pGoal, *m_pTile ;
	CSprite *m_pPrev, *m_pNext ;
	CSprite *m_pChapterNumber, *m_pStageNumber, *m_pStageName ;
	CSprite **m_pStagePreview_List ;

	bool m_bPressPrev, m_bPressNext ;

	float m_fBackgroundX ;

	FMOD::Sound *m_pBGM ;

public :
	static Scene* scene() ;

	SceneStageSelect() ;
	virtual ~SceneStageSelect() ;

	void Init() ;
	void Destroy() ;

	void Update(float dt) ;
	void Render() ;
private :
	void StageSelect() ;
	void AllocateStageName() ;
	void FreeStagePreview() ;
} ;