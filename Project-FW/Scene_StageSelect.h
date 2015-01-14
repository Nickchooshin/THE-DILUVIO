#pragma once

#include "Scene.h"
#include <vector>

class CSprite ;
class CScrollBackground ;

class SceneStageSelect : public Scene
{
private :
	CScrollBackground *m_pBackground ;
	CSprite *m_pBackground_Brick, *m_pMenuFrame ;
	CSprite *m_pProgress[5], *m_pPlayer, *m_pGoal ;
	CSprite *m_pPrev, *m_pNext, *m_pBack ;
	CSprite *m_pChapterNumber, *m_pStageNumber, *m_pStageName ;

	std::vector<CSprite*> m_StagePreview_List ;

	bool m_bPressPrev, m_bPressNext ;

	float m_fBackgroundX ;

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
	void FreeStageName() ;
} ;