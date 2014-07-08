#pragma once

#include "Objects.h"

class CHero : public CObjects
{
private :
	const float m_fVecSpeed, m_fVecJump ;
	float m_fVecAcc, m_fVecGravity ;

	bool m_bJump ;
	bool m_bGravity ;

	Vector m_vForce ;

	Size m_ImgSize, m_ColSize ;
	int m_nNowFrame ;
	int m_nStandFrame, m_nMoveFrame ;
	Position m_Stand_LeftIndex, m_Stand_RightIndex ;
	Position m_Move_LeftIndex, m_Move_RightIndex ;

	enum Direction { LEFT=0, RIGHT, LEFT_MOVE, RIGHT_MOVE } ;
	Direction m_Direction, m_prevDirection ;

public :
	CHero() ;
	~CHero() ;

	void Init() ;

	float GetPositionX() ;
	float GetPositionY() ;
	Vector GetForce() ;

	void SetJump(bool bFlag) ;

	void GravityAccReset() ;
	void Gravity() ;

	void Update() ;
private :
	void SetBoundingBox() ;

	void Move() ;
	void Animation() ;
} ;