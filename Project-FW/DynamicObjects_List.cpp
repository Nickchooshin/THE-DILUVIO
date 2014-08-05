#include "DynamicObjects_List.h"
#include "DynamicObjects.h"

#include "Collision.h"

#include <algorithm>

CDynamicObjects_List::CDynamicObjects_List() : m_pMainChar(NULL)
{
}
CDynamicObjects_List::~CDynamicObjects_List()
{
	m_pMainChar = NULL ;
	m_DynamicObjects_List.clear() ;
}

void CDynamicObjects_List::AddMainCharObjects(CDynamicObjects *pObjects)
{
	m_pMainChar = pObjects ;
	AddObjects(pObjects) ;
}

void CDynamicObjects_List::AddObjects(CDynamicObjects *pObjects)
{
	m_DynamicObjects_List.push_back(pObjects) ;
}

void CDynamicObjects_List::RemoveObjects(CDynamicObjects *pObjects)
{
	std::vector<CDynamicObjects*>::iterator iter ;
	std::vector<CDynamicObjects*>::iterator end = m_DynamicObjects_List.end() ;

	for(iter=m_DynamicObjects_List.begin(); iter!=end; iter++)
	{
		if((*iter)==pObjects)
		{
			m_DynamicObjects_List.erase(iter) ;
			return ;
		}
	}
}

void CDynamicObjects_List::Update()
{
	CDynamicObjects *pDynamicObjects ;
	std::vector<CDynamicObjects*>::iterator iter ;
	std::vector<CDynamicObjects*>::iterator end = m_DynamicObjects_List.end() ;

	for(iter=m_DynamicObjects_List.begin(); iter!=end; iter++)
	{
		pDynamicObjects = *iter ;
		pDynamicObjects->Update() ;
	}
}

void CDynamicObjects_List::Gravity()
{
	CDynamicObjects *pDynamicObjects ;
	std::vector<CDynamicObjects*>::iterator iter ;
	std::vector<CDynamicObjects*>::iterator end = m_DynamicObjects_List.end() ;

	for(iter=m_DynamicObjects_List.begin(); iter!=end; iter++)
	{
		pDynamicObjects = *iter ;
		pDynamicObjects->Gravity() ;
	}
}

bool Compare(CDynamicObjects* pDynamicObject1, CDynamicObjects* pDynamicObject2)
{
	return pDynamicObject1->GetPositionY() < pDynamicObject2->GetPositionY() ;
}

void CDynamicObjects_List::Collision(char coord)
{
	std::sort(m_DynamicObjects_List.begin(), m_DynamicObjects_List.end(), Compare) ;

	CCollision col ;
	const int size = m_DynamicObjects_List.size() ;

	for(int i=0; i<size; i++)
	{
		if(m_DynamicObjects_List[i]==m_pMainChar)
			continue ;

		for(int j=0; j<size; j++)
		{
			if(i==j)
				continue ;

			if(coord=='x' || coord=='X')
				col.XCollision(m_DynamicObjects_List[j], m_DynamicObjects_List[i]) ;
			else if(coord=='y' || coord=='Y')
				col.YCollision(m_DynamicObjects_List[j], m_DynamicObjects_List[i]) ;
		}
	}
}

const std::vector<CDynamicObjects*> CDynamicObjects_List::GetDynamicObjectsList()
{
	return m_DynamicObjects_List ;
}

const CDynamicObjects* CDynamicObjects_List::GetMainChar()
{
	return m_pMainChar ;
}