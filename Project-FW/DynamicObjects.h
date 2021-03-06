#pragma once

#include "Objects.h"

class CDynamicObjects : public CObjects
{
protected :
	float m_fVecSpeed, m_fVecJump ;
	float m_fVecAcc, m_fVecGravity ;
	float m_fGravityMultiples ;

	bool m_bJump ;
	bool m_bMultipleJump ;
	bool m_bAir ;
	bool m_bGravity ;
	bool m_bDeath ;

	enum DynamicState { AIR=1, UNDERWATER=2, SPARK=4 } ;
	char m_cDynamicState ;

	Vector m_vForce ;

public :
	CDynamicObjects() ;
	virtual ~CDynamicObjects() ;

	virtual void Init() = 0 ;

	virtual void Update() = 0 ;

	void SetJump(bool bFlag) ;
	void SetMultipleJump(bool bFlag) ;
	void SetAir(bool bFlag) ;
	void SetGravity(bool bFlag) ;
	void SetDeath(bool bFlag) ;

	void SetVecGravity(float fVecGravity) ;
	void SetGravityMultiples(float fGravityMultiples) ;

	const bool BeJump() ;
	const bool BeMultipleJump() ;
	const bool BeJumping() ;
	const bool BeAir() ;
	const bool BeGravity() ;
	const bool BeDeath() ;

	const Vector GetForce() ;
	const float GetVecGravity() ;
	
	void GravityAccReset() ;
	virtual void Gravity() ;
} ;