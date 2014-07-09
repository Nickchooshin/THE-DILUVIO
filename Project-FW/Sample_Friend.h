#pragma once

#include "Friends.h"

class CSampleFriend : public CFriends
{
private :
	Size m_ImgSize, m_ColSize ;
	int m_nNowFrame ;
	int m_nStandFrame, m_nAbsorbFrame, m_nReleaseFrame ;
	Position m_Stand_Index ;
	Position m_Absorb_Index ;
	Position m_Release_Index ;

	enum State { STAND=0, ABSORB, RELEASE } ;
	State m_State ;

public :
	CSampleFriend() ;
	~CSampleFriend() ;

	void Init() ;

	void Update() ;
private :
	void Animation() ;
} ;