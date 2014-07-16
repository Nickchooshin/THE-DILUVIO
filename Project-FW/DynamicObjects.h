#pragma once

#include "Objects.h"

class CDynamicObjects : public CObjects
{
protected :
	float m_fVecSpeed, m_fVecJump ;
	float m_fVecAcc, m_fVecGravity ;

	bool m_bJump ;
	bool m_bGravity ;

	Vector m_vForce ;

public :
	CDynamicObjects() ;
	virtual ~CDynamicObjects() ;

	virtual void Init() = 0 ;

	void SetJump(bool bFlag) ;
	void SetGravity(bool bFlag) ;

	const Vector GetForce() ;
	
	void GravityAccReset() ;
	virtual void Gravity() ;
} ;