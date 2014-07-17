#include "Friends_List.h"
#include "Friends.h"

#include <algorithm>
#include "Collision.h"

CFriends_List::CFriends_List() : m_nMaxFriends(0)
{
}
CFriends_List::~CFriends_List()
{
	Clear() ;
}

const int CFriends_List::GetSize()
{
	return m_Friends_List.size() ;
}

CFriends* CFriends_List::GetFriend(int index)
{
	const int size = m_Friends_List.size() ;

	if(size==0)
		return NULL ;
	else if(index<0)
		index = size + (index % size) ;
	else if(index>=size)
		index %= size ;

	return m_Friends_List[index] ;
}

bool CFriends_List::AddFriend(CFriends *pFriends)
{
	if(m_Friends_List.size()>=m_nMaxFriends)
	{
		delete pFriends ;

		return false ;
	}

	m_Friends_List.push_back(pFriends) ;

	return true ;
}

void CFriends_List::SetMaxFriends(int nMaxFriends)
{
	m_nMaxFriends = nMaxFriends ;

	if(nMaxFriends<m_nMaxFriends)
	{
		std::vector<CFriends*> temp ;
		const int size = m_Friends_List.size() ;
		for(int i=0; i<size; i++)
		{
			temp.push_back(m_Friends_List.front()) ;
			m_Friends_List.erase(m_Friends_List.begin()) ;
		}

		Clear() ;

		m_Friends_List.swap(temp) ;
	}
}

void CFriends_List::Clear()
{
	CFriends *temp ;
	std::vector<CFriends*>::iterator iter ;
	std::vector<CFriends*>::iterator end=m_Friends_List.end() ;

	for(iter=m_Friends_List.begin(); iter!=end; iter++)
	{
		temp = *iter ;
		delete temp ;
	}

	m_Friends_List.clear() ;
}

void CFriends_List::Gravity()
{
	CFriends *pFriends ;
	std::vector<CFriends*>::iterator iter ;
	std::vector<CFriends*>::iterator end=m_Friends_List.end() ;

	for(iter=m_Friends_List.begin(); iter!=end; iter++)
	{
		pFriends = *iter ;
		if(pFriends->GetRelease())
		{
			pFriends->Gravity() ;
			m_CollisionList.push_back(pFriends) ;
		}
	}
}

void CFriends_List::Update()
{
	CFriends *pFriends ;
	std::vector<CFriends*>::iterator iter ;
	std::vector<CFriends*>::iterator end=m_Friends_List.end() ;

	for(iter=m_Friends_List.begin(); iter!=end; iter++)
	{
		pFriends = *iter ;
		if(pFriends->GetRelease())
			pFriends->Update() ;
	}
}

void CFriends_List::Render()
{
	CFriends *pFriends ;
	std::vector<CFriends*>::iterator iter ;
	std::vector<CFriends*>::iterator end=m_Friends_List.end() ;

	for(iter=m_Friends_List.begin(); iter!=end; iter++)
	{
		pFriends = *iter ;
		if(pFriends->GetRelease())
			pFriends->Render() ;
	}
}

bool Compare(CFriends* pF1, CFriends* pF2)
{
	return pF1->GetPositionY() < pF2->GetPositionY() ;
}

void CFriends_List::Collision()
{
	std::sort(m_CollisionList.begin(), m_CollisionList.end(), Compare) ;

	int size = m_CollisionList.size() ;

	for(int i=0; i<size; i++)
	{
		for(int j=0; j<size; j++)
		{
			if(i==j)
				continue ;

			CCollision col ;
			col.YCollision(m_CollisionList[j], m_CollisionList[i]) ;
		}
	}

	m_CollisionList.clear() ;
}