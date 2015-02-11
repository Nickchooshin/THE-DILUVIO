#pragma once

#include "Singleton.h"

class CStageProgress ;

class SaveData : public Singleton<SaveData>
{
private :
	int m_nChapterProgress, m_nStageProgress, m_nTutorialProgress ;
	bool m_bExtra ;
	char m_cExtraProgress[9] ;

public :
	SaveData() ;
	~SaveData() ;

	void Save() ;
	void Load() ;

	void Reset() ;

	friend CStageProgress ;
} ;

#define g_SaveData SaveData::GetInstance()