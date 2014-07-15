#pragma once

#include "Objects.h"

class CFriends : public CObjects
{
protected :
	Size m_ImgSize, m_ColSize ;
	int m_nNowFrame ;
	int m_nStandFrame, m_nAbsorbFrame, m_nReleaseFrame ;
	Position m_Stand_Index ;
	Position m_Absorb_Index ;
	Position m_Release_Index ;
	Position m_Icon_Index ;

	enum State { STAND=0, ABSORB, RELEASE } ;
	State m_State ;

public :
	CFriends() ;
	virtual ~CFriends() ;

	Position GetIconIndex() ;

	virtual void Update() ;

protected :
	void LoadDat(char *filepath) ;
	void SetBoundingBox() ;

	virtual void Animation() ;
} ;