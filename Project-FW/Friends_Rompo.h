#pragma once

#include "Friends.h"

class CEffect_RompoDash ;

class CFriends_Rompo : public CFriends
{
private :
	CEffect_RompoDash *m_pEAbilityL, *m_pEAbilityR ;

public :
	CFriends_Rompo() ;
	~CFriends_Rompo() ;

	void Init() ;

	void Update() ;

	void Render() ;
private :
	void Dash(int x, int y, char cDirection) ;
} ;