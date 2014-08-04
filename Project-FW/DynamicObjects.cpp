#include "DynamicObjects.h"
#include "D3dDevice.h"

#include <stdio.h>

CDynamicObjects::CDynamicObjects() : m_fVecSpeed(0.0f), m_fVecJump(0.0f),
									 m_fVecAcc(0.0f), m_fVecGravity(0.0f),
									 m_fGravityMultiples(1.0f),
									 m_bJump(false),
									 m_bGravity(true),
									 m_bDeath(false),
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

void CDynamicObjects::SetDeath(bool bFlag)
{
	m_bDeath = bFlag ;
}

void CDynamicObjects::SetVecGravity(float fVecGravity)
{
	m_fVecGravity = fVecGravity ;
}

void CDynamicObjects::SetGravityMultiples(float fGravityMultiples)
{
	m_fGravityMultiples = fGravityMultiples ;
}

const bool CDynamicObjects::BeJump()
{
	return m_bJump ;
}

const bool CDynamicObjects::BeGravity()
{
	return m_bGravity ;
}

const bool CDynamicObjects::BeDeath()
{
	return m_bDeath ;
}

const Vector CDynamicObjects::GetForce()
{
	return m_vForce ;
}

const float CDynamicObjects::GetVecGravity()
{
	return m_fVecGravity ;
}

void CDynamicObjects::GravityAccReset()
{
	m_fVecAcc = 0.0f ;
}

void CDynamicObjects::Gravity()
{
	float fTime = g_D3dDevice->GetMoveTime() ;
	float fVecGravity = m_fVecGravity * fTime ;

	m_fVecAcc += fVecGravity ;
	m_vForce.y = m_fVecAcc * m_fGravityMultiples ;
	m_fY += m_vForce.y ;
	m_bGravity = true ;
	m_bJump = true ;

	if(m_fY<0.0f)
	{
		m_fY = 0.0f ;
		m_bGravity = false ;
		m_bJump = false ;
		GravityAccReset() ;
	}
}