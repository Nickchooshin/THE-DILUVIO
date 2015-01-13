#pragma once

#include "Singleton.h"

class CStageProgress : public Singleton<CStageProgress>
{
public :
	enum StageState { NONE=0, CLEAR, OVER } ;
private :
	const int m_nMaxStage ;
	int m_nStageProgress ;
	int m_nSelectStage ;

	StageState m_NowStageState ;

public :
	CStageProgress() ;
	~CStageProgress() ;

	void Init() ;

	const int GetStageProgress() const ;
	const StageState NowStageState() const ;

	void StageClear() ;
	void StageOver() ;
} ;

#define g_StageProgress CStageProgress::GetInstance()