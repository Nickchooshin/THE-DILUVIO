#pragma once

#include "Singleton.h"
#include <string>

class CStageProgress : public Singleton<CStageProgress>
{
public :
	enum StageState { NONE=0, CLEAR, OVER } ;
	enum MapType { GAME=0, EXTRA } ;
	static const int nChapterMaxStage[5] ;
private :
	int m_nSelectChapter, m_nSelectStage ;
	int m_nChapterMoveSelectedStageMax ;	// Chapter 가 이동될 때 선택되는 스테이지 최대치
	int m_nExtraSelectStage ;

	StageState m_NowStageState ;
	MapType m_MapType ;

	std::string m_strMapName[5][9] ;

public :
	CStageProgress() ;
	~CStageProgress() ;

	void Init() ;

	const int GetChapterProgress() const ;
	const int GetStageProgress() const ;
	const int GetTutorialProgress() ;
	const char GetExtraStageProgress(int index) const ;
	const int GetSelectChapter() const ;
	const int GetSelectStage() const ;
	const bool BeExtra() const ;
	const StageState NowStageState() const ;
	const MapType GetMapType() const ;

	const char* GetSelectMapName() ;

	bool NextStage() ;
	bool PrevStage() ;
	void NextChapter() ;
	void PrevChapter() ;

	void StageClear() ;
	void StageOver() ;
	bool LastStageClear() ;

	void SetMapType(MapType mapType) ;
private :
	bool NextStage_Game() ;
	bool PrevStage_Game() ;
	bool NextStage_Extra() ;
	bool PrevStage_Extra() ;

	bool TutorialProgressCheck(const char progress) ;
} ;

#define g_StageProgress CStageProgress::GetInstance()