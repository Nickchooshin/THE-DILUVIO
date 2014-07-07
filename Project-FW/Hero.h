#pragma once

#include "Objects.h"

class CHero : public CObjects
{
private :
	const float m_fVecSpeed ;
	float m_fVecAcc, m_fVecGravity ;

	bool m_bJump ;

public :
	CHero() ;
	~CHero() ;

	void Init() ;

	float GetPositionX() ;
	float GetPositionY() ;

	void GravityReset() ;

	void Update() ;
private :
	void SetBoundingBox() ;

	void Move() ;
} ;