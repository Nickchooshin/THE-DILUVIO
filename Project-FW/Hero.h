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
	int m_nStandFrame, m_nMoveFrame, m_nJumpFrame, m_nAbsorbFrame, m_nReleaseFrame ;
	Position m_Stand_LeftIndex, m_Stand_RightIndex ;
	Position m_Move_LeftIndex, m_Move_RightIndex ;
	Position m_Jump_LeftIndex, m_Jump_RightIndex ;
	Position m_Absorb_LeftIndex, m_Absorb_RightIndex ;
	Position m_Release_LeftIndex, m_Release_RightIndex ;

	//enum State { LEFT=0, RIGHT, LEFT_MOVE, RIGHT_MOVE, LEFT_JUMP, RIGHT_JUMP, LEFT_ABSORB, RIGHT_ABSORB, LEFT_RELEASE, RIGHT_RELEASE } ;
	enum State { LEFT=0, LEFT_MOVE, LEFT_JUMP, LEFT_ABSORB, LEFT_RELEASE,
				 RIGHT, RIGHT_MOVE, RIGHT_JUMP, RIGHT_ABSORB, RIGHT_RELEASE } ;
	State m_State, m_prevState ;

public :
	CHero() ;
	~CHero() ;

	void Init() ;

	float GetPositionX() ;
	float GetPositionY() ;
	Vector GetForce() ;

	void SetJump(bool bFlag) ;
	void SetGravity(bool bFlag) ;

	void GravityAccReset() ;
	void Gravity() ;

	void Update() ;
private :
	void SetBoundingBox() ;

	void Move() ;
	void Animation() ;
} ;