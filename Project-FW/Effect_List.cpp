#include "Effect_List.h"
#include "Effect.h"
#include "DynamicObjects.h"
#include "Collision.h"

#include "DynamicObjects_List.h"

#include <stdio.h>

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

void CEffect_List::Clear()
{
	m_Effect_List.clear() ;
}

void CEffect_List::Collision()
{
	CCollision col ;

	CDynamicObjects *pObject ;
	CEffect *pEffect ;
	std::vector<CDynamicObjects*> DynamicObjects_List = g_DynamicObjects_List->GetDynamicObjectsList() ;
	std::vector<CDynamicObjects*>::iterator iter_o, end_o=DynamicObjects_List.end() ;
	std::vector<CEffect*>::iterator iter_e, end_e=m_Effect_List.end() ;

	for(iter_o=DynamicObjects_List.begin(); iter_o!=end_o; iter_o++)
	{
		pObject = (*iter_o) ;

		for(iter_e=m_Effect_List.begin(); iter_e!=end_e; iter_e++)
		{
			pEffect = (*iter_e) ;
			bool bCollision=false ;

			bCollision = col.DotCirleCollision(pObject, pEffect) ;
			if(bCollision)
				pEffect->Effect(pObject) ;
		}
	}
}