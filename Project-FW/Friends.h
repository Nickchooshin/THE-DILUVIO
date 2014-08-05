#pragma once

#include "DynamicObjects.h"

//
class CEffect_SparkImpact ;
//

class CFriends : public CDynamicObjects
{
protected :
	//
	CEffect_SparkImpact *m_pESparkImpact ;
	//
	Size m_ImgSize, m_ColSize ;
	int m_nNowFrame ;
	int m_nStandFrame, m_nAbsorbFrame, m_nReleaseFrame ;
	Position m_Stand_Index ;
	Position m_Absorb_Index ;
	Position m_Release_Index ;
	Position m_Icon_Index ;

	bool m_bRelease ;
	bool m_bStun ;
	
	float m_fAnimationTime ;

	enum State { STAND=0, ABSORB, RELEASE } ;
	State m_State, m_prevState ;

public :
	CFriends() ;
	virtual ~CFriends() ;

	virtual void Init() = 0 ;

	void Absorb() ;
	void Release() ;

	const bool GetRelease() ;
	const Position GetIconIndex() ;

	virtual void Update() ;

	//
	virtual void SendEventMessage(char *EventMessage) ;
	virtual void Render() ;
protected :
	void LoadDat(char *filepath) ;
	void SetBoundingBox() ;

	virtual void Animation() ;
} ;