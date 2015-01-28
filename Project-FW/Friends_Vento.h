#pragma once

#include "Friends.h"
#include <fmod.hpp>

class CEffect_VentoAbility ;

class CFriends_Vento : public CFriends
{
private :
	CEffect_VentoAbility *m_pEAbility ;

	FMOD::Sound *m_pSEAbility ;

public :
	CFriends_Vento() ;
	~CFriends_Vento() ;

	void Init() ;

	void Update() ;

	void Render() ;
} ;	