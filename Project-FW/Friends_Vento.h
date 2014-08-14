#pragma once

#include "Friends.h"

class CEffect_VentoAbility ;

class CFriends_Vento : public CFriends
{
private :
	CEffect_VentoAbility *m_pEAbility ;

public :
	CFriends_Vento() ;
	~CFriends_Vento() ;

	void Init() ;

	void Update() ;

	void Render() ;
} ;	