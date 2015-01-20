#include "StageProgress.h"
#include <stdio.h>

const int CStageProgress::nChapterMaxStage[5] = {8, 9, 8, 7, 5 } ;

CStageProgress::CStageProgress() : m_nChapterProgress(5), m_nStageProgress(5),
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
	}
}

void CStageProgress::StageOver()
{
	m_NowStageState = OVER ;
}