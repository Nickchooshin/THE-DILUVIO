#include "DynamicObjects.h"

CDynamicObjects::CDynamicObjects() : m_fVecSpeed(0.0f), m_fVecJump(0.0f),
									 m_fVecAcc(0.0f), m_fVecGravity(0.0f),
									 m_bJump(false),
									 m_bGravity(true),
									 m_vForce(0.0f, 0.0f)
{
}
CDynamicObjects::~CDynamicObjects()
{
}

void CDynamicObjects::SetJump(bool bFlag)
{
	m_bJump = bFlag ;
}

void CDynamicObjects::SetGravity(bool bFlag)
{
	m_bGravity = bFlag ;
}

const Vector CDynamicObjects::GetForce()
{
	return m_vForce ;
}

void CDynamicObjects::GravityAccReset()
{
	m_fVecAcc = 0.0f ;
}

void CDynamicObjects::Gravity()
{
	m_fVecAcc += m_fVecGravity ;
	m_vForce.y = m_fVecAcc ;
	m_fY += m_vForce.y ;
	m_bGravity = true ;

	if(m_fY<32.0f)
	{
		m_fY = 32.0f ;
		m_bGravity = false ;
		SetJump(false) ;
		GravityAccReset() ;
	}
}