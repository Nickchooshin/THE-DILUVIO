#pragma once

#include "Friends.h"

class CEffect_OkuloAbility ;

class CFriends_Okulo : public CFriends
{
private :
	CEffect_OkuloAbility *m_pEAbility ;

public :
	CFriends_Okulo() ;
	~CFriends_Okulo() ;

	void Init() ;

	void Update() ;

	void Render() ;
} ;