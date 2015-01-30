#pragma once

#include "Singleton.h"
#include <string>

class CStageProgress : public Singleton<CStageProgress>
{
public :
	enum StageState { NONE=0, CLEAR, OVER } ;
	static const int nChapterMaxStage[5] ;
private :
	int m_nChapterProgress, m_nStageProgress, m_nTutorialProgress ;
	int m_nSelectChapter, m_nSelectStage ;
	int m_nChapterMoveSelectedStageMax ;	// Chapter 가 이동될 때 선택되는 스테이지 최대치

	StageState m_NowStageState ;

	std::string m_strMapName[5][9] ;

public :
	CStageProgress() ;
	~CStageProgress() ;

	void Init() ;

	const int GetChapterProgress() const ;
	const int GetStageProgress() const ;
	const int GetTutorialProgress() ;
	const int GetSelectChapter() const ;
	const int GetSelectStage() const ;
	const StageState NowStageState() const ;

	const char* GetSelectMapName() ;

	bool NextStage() ;
	bool PrevStage() ;
	void NextChapter() ;
	void PrevChapter() ;

	void StageClear() ;
	void StageOver() ;
	bool LastStageClear() ;

private :
	void StageProgressSave() ;
	bool StageProgressLoad() ;
	bool TutorialProgressCheck(const char progress) ;
} ;

#define g_StageProgress CStageProgress::GetInstance()