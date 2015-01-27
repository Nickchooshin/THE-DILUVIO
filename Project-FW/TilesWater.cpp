#include "TilesWater.h"
#include "DynamicObjects.h"

#include "D3dDevice.h"

#include "DynamicObjects_List.h"

DWORD CTilesWater::m_dwMultipleJumpDelay = 0 ;
bool CTilesWater::m_bMultipleJump = false ;

CTilesWater::CTilesWater()
{
	m_bGravityMultiples = true ;
	m_bEffect = true ;
}
CTilesWater::~CTilesWater()
{
}

void CTilesWater::Effect1(CDynamicObjects* pDynamicObject)
{
	pDynamicObject->SendEventMessage("WATER") ;

	pDynamicObject->SetGravityMultiples(0.5f) ;
	pDynamicObject->SetMultipleJump(true) ;
	//pDynamicObject->SetDeath(true) ;

	if(pDynamicObject!=g_DynamicObjects_List->GetMainChar())
		return ;

	if(m_bMultipleJump)
	{
		DWORD dwNowTime = timeGetTime() ;
		DWORD dwElapsedTime = dwNowTime - m_dwMultipleJumpDelay ;
		float fDelay = dwElapsedTime * 0.001f ;

		if(fDelay>=0.5f)
		{
			m_bMultipleJump = false ;

			pDynamicObject->SetJump(false) ;
		}
	}

	if(!m_bMultipleJump && pDynamicObject->BeJump())
	{
		static DWORD time=0 ;
		DWORD now = timeGetTime() ;

		m_bMultipleJump = true ;
		m_dwMultipleJumpDelay = timeGetTime() ;
	}
}