#pragma once

#include "Singleton.h"
#include <vector>

class CEffect ;

class CEffect_List : public Singleton<CEffect_List>
{
private :
	std::vector<CEffect*> m_Effect_List ;

public :
	CEffect_List() ;
	~CEffect_List() ;

	void AddEffect(CEffect* pEffect) ;
	void Clear() ;

	void Collision() ;
} ;

#define g_Effect_List CEffect_List::GetInstance()