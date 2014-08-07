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

void CDynamicObjects_List::AddMainCharObjects(CDynamicObjects *pDynamicObject)
{
	m_pMainChar = pDynamicObject ;
	AddObjects(pDynamicObject) ;
}

void CDynamicObjects_List::AddObjects(CDynamicObjects *pDynamicObject)
{
	m_DynamicObjects_List.push_back(pDynamicObject) ;
}

void CDynamicObjects_List::RemoveObjects(CDynamicObjects *pDynamicObject)
{
	CDynamicObjects *pTemp ;
	const int size = m_DynamicObjects_List.size() ;

	for(int i=0; i<size; i++)
	{
		pTemp = m_DynamicObjects_List[i] ;

		if(pTemp==pDynamicObject)
		{
			m_DynamicObjects_List.erase(m_DynamicObjects_List.begin() + i) ;
			return ;
		}
	}
}

void CDynamicObjects_List::Update()
{
	CDynamicObjects *pDynamicObject ;
	const int size = m_DynamicObjects_List.size() ;

	for(int i=0; i<size; i++)
	{
		pDynamicObject = m_DynamicObjects_List[i] ;
		pDynamicObject->Update() ;
	}
}

void CDynamicObjects_List::Gravity()
{
	CDynamicObjects *pDynamicObject ;
	const int size = m_DynamicObjects_List.size() ;

	for(int i=0; i<size; i++)
	{
		pDynamicObject = m_DynamicObjects_List[i] ;
		pDynamicObject->Gravity() ;
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