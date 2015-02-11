#include "StageProgress.h"
#include "SaveData.h"
#include <stdio.h>

const int CStageProgress::nChapterMaxStage[5] = {8, 9, 8, 7, 5 } ;

const char TUTORIAL_1 = 1 ;
const char TUTORIAL_2 = 2 ;
const char TUTORIAL_3 = 4 ;
const char TUTORIAL_4 = 8 ;
const char TUTORIAL_5 = 16 ;
const char TUTORIAL_6 = 32 ;
const char TUTORIAL_7 = 64 ;

CStageProgress::CStageProgress() : m_nSelectChapter(1), m_nSelectStage(1),
								   m_nChapterMoveSelectedStageMax(1),
								   m_nExtraSelectStage(1),
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

	g_SaveData->Load() ;

	m_nSelectChapter = g_SaveData->m_nChapterProgress ;
	m_nSelectStage = g_SaveData->m_nStageProgress ;
	m_nChapterMoveSelectedStageMax = m_nSelectStage ;
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
	return g_SaveData->m_nChapterProgress ;
}

const int CStageProgress::GetStageProgress() const
{
	return g_SaveData->m_nStageProgress ;
}

const int CStageProgress::GetTutorialProgress()
{
	if(m_MapType==GAME)
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
	}

	return 0 ;
}

const char CStageProgress::GetExtraStageProgress(int index) const
{
	return g_SaveData->m_cExtraProgress[index] ;
}

const int CStageProgress::GetSelectChapter() const
{
	switch(m_MapType)
	{
	case GAME :
		return m_nSelectChapter ;

	case EXTRA :
		return 1 ;
	}
}

const int CStageProgress::GetSelectStage() const
{
	switch(m_MapType)
	{
	case GAME :
		return m_nSelectStage ;

	case EXTRA :
		return m_nExtraSelectStage ;
	}
}

const bool CStageProgress::BeExtra() const
{
	return g_SaveData->m_bExtra ;
}

const CStageProgress::StageState CStageProgress::NowStageState() const
{
	return m_NowStageState ;
}

const CStageProgress::MapType CStageProgress::GetMapType() const
{
	return m_MapType ;
}

const char* CStageProgress::GetSelectMapName()
{
	static char strMapName[20] ;

	switch(m_MapType)
	{
	case GAME :
		return m_strMapName[m_nSelectChapter-1][m_nSelectStage-1].c_str() ;

	case EXTRA :
		sprintf_s(strMapName, "Extra/EXTRA%03d", m_nExtraSelectStage) ;
		return strMapName ;
	}
}

bool CStageProgress::NextStage()
{
	switch(m_MapType)
	{
	case GAME :
		return NextStage_Game() ;

	case EXTRA :
		return NextStage_Extra() ;
	}
}

bool CStageProgress::PrevStage()
{
	switch(m_MapType)
	{
	case GAME :
		return PrevStage_Game() ;

	case EXTRA :
		return PrevStage_Extra() ;
	}
}

void CStageProgress::NextChapter()
{
	if(m_nSelectChapter<g_SaveData->m_nChapterProgress)
	{
		++m_nSelectChapter ;

		const int MaxStage = nChapterMaxStage[m_nSelectChapter-1] ;

		if(m_nChapterMoveSelectedStageMax>MaxStage)
			m_nSelectStage = MaxStage ;
		else
			m_nSelectStage = m_nChapterMoveSelectedStageMax ;
	}
}

void CStageProgress::PrevChapter()
{
	if(m_nSelectChapter>1)
	{
		--m_nSelectChapter ;

		const int MaxStage = nChapterMaxStage[m_nSelectChapter-1] ;

		if(m_nChapterMoveSelectedStageMax>MaxStage)
			m_nSelectStage = MaxStage ;
		else
			m_nSelectStage = m_nChapterMoveSelectedStageMax ;
	}
}

void CStageProgress::StageClear()
{
	m_NowStageState = CLEAR ;

	if(m_MapType==GAME && m_nSelectChapter==g_SaveData->m_nChapterProgress && m_nSelectStage==g_SaveData->m_nStageProgress)
	{
		if(g_SaveData->m_nStageProgress<nChapterMaxStage[m_nSelectChapter-1])
		{
			++g_SaveData->m_nStageProgress ;
		}
		else if(g_SaveData->m_nChapterProgress<5)
		{
			++g_SaveData->m_nChapterProgress ;
			g_SaveData->m_nStageProgress = 1 ;
		}

		g_SaveData->Save() ;
	}
	else if(m_MapType==EXTRA)
	{
		if(g_SaveData->m_cExtraProgress[m_nExtraSelectStage-1]==0)
		{
			g_SaveData->m_cExtraProgress[m_nExtraSelectStage-1] = 1 ;

			g_SaveData->Save() ;

			bool bAllClear=true ;
			for(int i=0; i<9; i++)
			{
				if(g_SaveData->m_cExtraProgress[i]==0)
				{
					bAllClear = false ;
					break ;
				}
			}

			if(bAllClear)
			{
				g_SaveData->Reset() ;
				return ;
			}
		}
	}
}

void CStageProgress::StageOver()
{
	m_NowStageState = OVER ;
}

bool CStageProgress::LastStageClear()
{
	if(m_MapType==GAME && m_NowStageState==CLEAR)
	{
		if(m_nSelectChapter==5 && m_nSelectStage==nChapterMaxStage[m_nSelectChapter-1])
		{
			g_SaveData->m_bExtra = true ;
			return true ;
		}
	}

	return false ;
}

void CStageProgress::SetMapType(MapType mapType)
{
	m_MapType = mapType ;
}

bool CStageProgress::NextStage_Game()
{
	if(m_nSelectStage<nChapterMaxStage[m_nSelectChapter-1])
	{
		if(m_nSelectChapter<g_SaveData->m_nChapterProgress || m_nSelectStage<g_SaveData->m_nStageProgress)
		{
			++m_nSelectStage ;
			m_nChapterMoveSelectedStageMax = m_nSelectStage ;

			return true ;
		}
	}
	else if(m_nSelectChapter<5)
	{
		if(m_nSelectChapter<g_SaveData->m_nChapterProgress)
		{
			++m_nSelectChapter ;
			m_nSelectStage = 1 ;
			m_nChapterMoveSelectedStageMax = m_nSelectStage ;

			return true ;
		}
	}

	return false ;
}

bool CStageProgress::PrevStage_Game()
{
	if(m_nSelectStage>1)
	{
		--m_nSelectStage ;
		m_nChapterMoveSelectedStageMax = m_nSelectStage ;

		return true ;
	}
	else if(m_nSelectChapter>1)
	{
		--m_nSelectChapter ;
		m_nSelectStage = nChapterMaxStage[m_nSelectChapter-1] ;
		m_nChapterMoveSelectedStageMax = m_nSelectStage ;

		return true ;
	}

	return false ;
}

bool CStageProgress::NextStage_Extra()
{
	if(m_nExtraSelectStage<9)
	{
		++m_nExtraSelectStage ;

		return true ;
	}

	return false ;
}

bool CStageProgress::PrevStage_Extra()
{
	if(m_nExtraSelectStage>1)
	{
		--m_nExtraSelectStage ;
		
		return true ;
	}

	return false ;
}

bool CStageProgress::TutorialProgressCheck(const char progress)
{
	if((g_SaveData->m_nTutorialProgress & progress) == progress)
		return true ;

	g_SaveData->m_nTutorialProgress |= progress ;
	g_SaveData->Save() ;

	return false ;
}