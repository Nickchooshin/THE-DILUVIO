#pragma once

#include "Friends.h"

class CEffect_MakzeloAbility ;

class CFriends_Makzelo : public CFriends
{
private :
	CEffect_MakzeloAbility *m_pEAbility ;

public :
	CFriends_Makzelo() ;
	~CFriends_Makzelo() ;

	void Init() ;

	void Update() ;

	void Render() ;
} ;