#include "StageProgress.h"

CStageProgress::CStageProgress() : m_nMaxStage(10),
								   m_nStageProgress(1),
								   m_nSelectStage(1),
								   m_NowStageState(NONE)
{
}
CStageProgress::~CStageProgress()
{
}

void CStageProgress::Init()
{
	m_NowStageState = NONE ;
}

const int CStageProgress::GetStageProgress() const
{
	return m_nStageProgress ;
}

const CStageProgress::StageState CStageProgress::NowStageState() const
{
	return m_NowStageState ;
}

void CStageProgress::StageClear()
{
	m_NowStageState = CLEAR ;

	if(m_nSelectStage==m_nStageProgress && m_nStageProgress<m_nMaxStage)
		++m_nStageProgress ;
}

void CStageProgress::StageOver()
{
	m_NowStageState = OVER ;
}