#pragma once

#include "DynamicObjects.h"
#include <fmod.hpp>

class CEffect_SparkImpact ;

class CFriends : public CDynamicObjects
{
protected :
	CEffect_SparkImpact *m_pESparkImpact ;
	Size m_ImgSize, m_ColSize ;
	int m_nNowFrame ;
	int m_nStandFrame, m_nAbsorbFrame, m_nReleaseFrame, m_nStunFrame ;
	Position m_Stand_Index, m_Absorb_Index, m_Release_Index, m_Stun_Index, m_Icon_Index ;

	bool m_bEaten ;
	bool m_bRelease ;
	bool m_bStun, m_bShock ;
	bool m_bRespiration ;
	
	float m_fAnimationTime ;
	int m_nRanchoAlpha ;

	bool m_bSEWater, m_bSESpark, m_bSEAbility ;
	FMOD::Sound *m_pSEWater, *m_pSESpark, *m_pSEAbility ;

	enum State { STAND=0, ABSORB, RELEASE, STUN } ;
	State m_State, m_prevState ;

public :
	CFriends() ;
	virtual ~CFriends() ;

	virtual void Init() = 0 ;

	virtual void Absorb() ;
	virtual void Release() ;

	const bool GetRelease() ;
	const Position GetIconIndex() ;
	const bool BeStand() ;

	virtual void Update() ;

	virtual void SendEventMessage(char *EventMessage, void *pData) ;
	virtual void EventClear() ;

	virtual void Render() ;
protected :
	void LoadDat(char *filepath) ;
	void SetBoundingBox() ;

	virtual void Animation() ;
} ;