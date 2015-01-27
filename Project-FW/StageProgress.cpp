#include "StageProgress.h"
#include <stdio.h>

const int CStageProgress::nChapterMaxStage[5] = {8, 9, 8, 7, 5 } ;

const char TUTORIAL_1 = 1 ;
const char TUTORIAL_2 = 2 ;
const char TUTORIAL_3 = 4 ;
const char TUTORIAL_4 = 8 ;
const char TUTORIAL_5 = 16 ;
const char TUTORIAL_6 = 32 ;
const char TUTORIAL_7 = 64 ;

CStageProgress::CStageProgress() : m_nChapterProgress(1), m_nStageProgress(1), m_nTutorialProgress(0),
								   m_nSelectChapter(1), m_nSelectStage(1),
								   m_NowStageState(NONE)
{
	FILE *pFile ;
	char filepath[1024], name[1024] ;

	for(int i=0; i<5; i++)
	{
		sprintf_s(filepath, "Resource/Data/Chapter/Chapter%d.dat", i+1) ;
		pFile = fopen(filepath, "r") ;

		for(int j=0; j<nChapterMaxStage[i]; j++)
		{
			fscanf(pFile, "%s", name) ;
			m_strMapName[i][j] = name ;
		}

		fclose(pFile) ;
	}

	StageProgressLoad() ;
}
CStageProgress::~CStageProgress()
{
}

void CStageProgress::Init()
{
	m_NowStageState = NONE ;
}

const int CStageProgress::GetChapterProgress() const
{
	return m_nChapterProgress ;
}

const int CStageProgress::GetStageProgress() const
{
	return m_nStageProgress ;
}

const int CStageProgress::GetTutorialProgress()
{
	if(m_nSelectChapter==1)
	{
		if(m_nSelectStage==1 && !TutorialProgressCheck(TUTORIAL_1))
			return 1 ;
		else if(m_nSelectStage==2 && !TutorialProgressCheck(TUTORIAL_2))
			return 2 ;
	}
	else if(m_nSelectChapter==2)
	{
		if(m_nSelectStage==1 && !TutorialProgressCheck(TUTORIAL_3))
			return 3 ;
		else if(m_nSelectStage==5 && !TutorialProgressCheck(TUTORIAL_4))
			return 4 ;
	}
	else if(m_nSelectChapter==3)
	{
		if(m_nSelectStage==1 && !TutorialProgressCheck(TUTORIAL_5))
			return 5 ;
		else if(m_nSelectStage==6 && !TutorialProgressCheck(TUTORIAL_6))
			return 6 ;
	}
	else if(m_nSelectChapter==4)
	{
		if(m_nSelectStage==1 && !TutorialProgressCheck(TUTORIAL_7))
			return 7 ;
	}

	return 0 ;
}

const int CStageProgress::GetSelectChapter() const
{
	return m_nSelectChapter ;
}

const int CStageProgress::GetSelectStage() const
{
	return m_nSelectStage ;
}

const CStageProgress::StageState CStageProgress::NowStageState() const
{
	return m_NowStageState ;
}

bool CStageProgress::NextStage()
{
	if(m_nSelectStage<nChapterMaxStage[m_nSelectChapter-1])
	{
		if(m_nSelectChapter<m_nChapterProgress || m_nSelectStage<m_nStageProgress)
		{
			++m_nSelectStage ;

			return true ;
		}
	}
	else if(m_nSelectChapter<5)
	{
		if(m_nSelectChapter<m_nChapterProgress)
		{
			++m_nSelectChapter ;
			m_nSelectStage = 1 ;

			return true ;
		}
	}

	return false ;
}

const char* CStageProgress::GetSelectMapName()
{
	return m_strMapName[m_nSelectChapter-1][m_nSelectStage-1].c_str() ;
}

bool CStageProgress::PrevStage()
{
	if(m_nSelectStage>1)
	{
		--m_nSelectStage ;

		return true ;
	}
	else if(m_nSelectChapter>1)
	{
		--m_nSelectChapter ;
		m_nSelectStage = nChapterMaxStage[m_nSelectChapter-1] ;

		return true ;
	}

	return false ;
}

void CStageProgress::StageClear()
{
	m_NowStageState = CLEAR ;

	if(m_nSelectChapter==m_nChapterProgress && m_nSelectStage==m_nStageProgress)
	{
		if(m_nStageProgress<nChapterMaxStage[m_nSelectChapter-1])
		{
			++m_nStageProgress ;
		}
		else if(m_nChapterProgress<5)
		{
			++m_nChapterProgress ;
			m_nStageProgress = 1 ;
		}

		StageProgressSave() ;
	}
}

void CStageProgress::StageOver()
{
	m_NowStageState = OVER ;
}

bool CStageProgress::LastStageClear()
{
	if(m_NowStageState==CLEAR)
	{
		if(m_nSelectChapter==5 && m_nSelectStage==nChapterMaxStage[m_nSelectChapter-1])
			return true ;
	}

	return false ;
}

void CStageProgress::StageProgressSave()
{
	FILE *pFile = fopen("Resource/Data/.sav", "wb") ;

	fprintf(pFile, "%d%d%d", m_nChapterProgress, m_nStageProgress, m_nTutorialProgress) ;

	fclose(pFile) ;
}

bool CStageProgress::StageProgressLoad()
{
	FILE *pFile = fopen("Resource/Data/.sav", "rb") ;

	if(pFile==NULL)
		return false ;

	char value[4] ;

	fscanf(pFile, "%s", &value) ;
	m_nChapterProgress = value[0] - '0' ;
	m_nStageProgress = value[1] - '0' ;
	m_nTutorialProgress = value[2] - '0' ;

	fclose(pFile) ;

	return true ;
}

bool CStageProgress::TutorialProgressCheck(const char progress)
{
	if((m_nTutorialProgress & progress) == progress)
		return true ;

	m_nTutorialProgress |= progress ;
	StageProgressSave() ;

	return false ;
}