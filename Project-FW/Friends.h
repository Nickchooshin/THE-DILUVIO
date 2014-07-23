#pragma once

#include "DynamicObjects.h"

class CFriends : public CDynamicObjects
{
protected :
	Size m_ImgSize, m_ColSize ;
	int m_nNowFrame ;
	int m_nStandFrame, m_nAbsorbFrame, m_nReleaseFrame ;
	Position m_Stand_Index ;
	Position m_Absorb_Index ;
	Position m_Release_Index ;
	Position m_Icon_Index ;

	bool m_bRelease ;
	
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
protected :
	void LoadDat(char *filepath) ;
	void SetBoundingBox() ;

	virtual void Animation() ;
} ;