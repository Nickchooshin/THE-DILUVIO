#pragma once

#include "Friends.h"

class CEffect_RompoDash ;

class CFriends_Rompo : public CFriends
{
private :
	CEffect_RompoDash *m_pEAbilityL, *m_pEAbilityR ;
	bool m_bUsingAbility ;

	FMOD::Sound *m_pSEDash ;

public :
	CFriends_Rompo() ;
	~CFriends_Rompo() ;

	void Init() ;

	void Absorb() ;

	void Update() ;

	void Render() ;
private :
	void Dash(int x, int y, char cDirection) ;
} ;