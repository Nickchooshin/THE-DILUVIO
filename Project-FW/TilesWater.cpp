#include "TilesWater.h"
#include "DynamicObjects.h"

#include "D3dDevice.h"

DWORD CTilesWater::m_dwMultipleJumpDelay = 0 ;
bool CTilesWater::m_bMultipleJump = false ;

CTilesWater::CTilesWater()
{
	m_bGravityMultiples = true ;
}
CTilesWater::~CTilesWater()
{
}

void CTilesWater::Effect1(CDynamicObjects* pDynamicObject)
{
	if( m_CollisionDirection & COLLISION_UP ||
		m_CollisionDirection & COLLISION_DOWN )
	{
		pDynamicObject->SetGravityMultiples(0.5f) ;
		//pDynamicObject->SetJump(false) ;
		pDynamicObject->SetGravity(false) ;
		//pDynamicObject->SetDeath(true) ;

		if(m_bMultipleJump)
		{
			DWORD dwNowTime = timeGetTime() ;
			DWORD dwElapsedTime = dwNowTime - m_dwMultipleJumpDelay ;
			float fDelay = dwElapsedTime * 0.001f ;

			//if(dwElapsedTime>=100)
			if(fDelay>=0.6f)
			{
				//m_dwMultipleJumpDelay = dwNowTime - (dwElapsedTime % 600) ;
				m_bMultipleJump = false ;

				pDynamicObject->SetJump(false) ;
				pDynamicObject->SetGravity(false) ;
			}
		}

		if(!m_bMultipleJump && pDynamicObject->BeJump())
		{
			static DWORD time=0 ;
			DWORD now = timeGetTime() ;

			m_bMultipleJump = true ;
			//if(m_dwMultipleJumpDelay==0)
			m_dwMultipleJumpDelay = timeGetTime() ;
		}
	}
}