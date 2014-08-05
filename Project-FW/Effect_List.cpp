#include "Effect_List.h"
#include "Effect.h"
#include <algorithm>

CEffect_List::CEffect_List()
{
}
CEffect_List::~CEffect_List()
{
	Clear() ;
}

void CEffect_List::AddEffect(CEffect *pEffect)
{
	m_Effect_List.push_back(pEffect) ;
}

/*void CEffect_List::RemoveEffect(CEffect *pEffect)
{
	std::vector<CEffect*>::iterator iter ;
	std::vector<CEffect*>::iterator end=m_Effect_List.end() ;

	for(iter=m_Effect_List.begin(); iter!=end; iter++)
	{
		if(pEffect==(*iter))
		{
			m_Effect_List.erase(iter) ;
			return ;
		}
	}
}*/

void CEffect_List::Clear()
{
	m_Effect_List.clear() ;
}