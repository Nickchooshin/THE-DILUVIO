#pragma once

#include "DynamicObjects.h"

class CFriendChange_UI ;
class CEffect_Bubble ;
class CEffect_Soul ;

class CHero : public CDynamicObjects
{
private :
	Size m_ImgSize ;
	int m_nNowFrame ;
	int m_nStandFrame, m_nMoveFrame, m_nJumpFrame, m_nAbsorbFrame, m_nReleaseFrame ;
	Position m_Stand_LeftIndex, m_Stand_RightIndex ;
	Position m_Move_LeftIndex, m_Move_RightIndex ;
	Position m_Jump_LeftIndex, m_Jump_RightIndex ;
	Position m_Absorb_LeftIndex, m_Absorb_RightIndex ;
	Position m_Release_LeftIndex, m_Release_RightIndex ;

	float m_fTime, m_fAnimationTime ;

	//enum State { LEFT=0, RIGHT, LEFT_MOVE, RIGHT_MOVE, LEFT_JUMP, RIGHT_JUMP, LEFT_ABSORB, RIGHT_ABSORB, LEFT_RELEASE, RIGHT_RELEASE } ;
	enum State { LEFT=0, LEFT_MOVE, LEFT_JUMP, LEFT_ABSORB, LEFT_RELEASE,
				 RIGHT, RIGHT_MOVE, RIGHT_JUMP, RIGHT_ABSORB, RIGHT_RELEASE } ;
	State m_State, m_prevState ;

	bool m_bDeath, m_bReleaseAbsorb, m_bRespiration ;

	enum DYING { SINK=0, BUBBLE, FADE_AWAY, SOUL_OUT, SOUL } ;
	DYING m_Dying ;

	CFriendChange_UI *m_pFC_UI ;
	CEffect_Bubble *m_pEffect_Bubble ;
	CEffect_Soul *m_pEffect_Soul ;

public :
	CHero() ;
	~CHero() ;

	void Init() ;

	Direction GetDirection() ;

	void Update() ;

	void Render() ;

	void SendEventMessage(char *EventMessage, void *pData) ;
	void EventClear() ;
private :
	void SetBoundingBox() ;

	void Move() ;
	void Death() ;
	void Animation() ;
} ;