#pragma once

#include "Friends.h"

class CEffect_RompoDash ;

class CFriends_Rompo : public CFriends
{
private :
	CEffect_RompoDash *m_pEAbility ;

public :
	CFriends_Rompo() ;
	~CFriends_Rompo() ;

	void Init() ;

	void Update() ;

	void Render() ;
} ;