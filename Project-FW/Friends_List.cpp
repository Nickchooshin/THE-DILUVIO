#include "Friends_List.h"
#include "Friends.h"

#include "DynamicObjects_List.h"

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

CFriends* CFriends_List::GetFriend(int tileX, int tileY)
{
	CFriends *pFriend ;
	const int size = m_Friends_List.size() ;

	for(int i=0; i<size; i++)
	{
		pFriend = m_Friends_List[i] ;

		if(pFriend->GetRelease())
		{
			int x = (int)(pFriend->GetPositionX() / 64.0f) ;
			int y = (int)((pFriend->GetPositionY() + 32.0f) / 64.0f) ;

			if(tileX==x && tileY==y)
				return pFriend ;
		}
	}

	return NULL ;
}

bool CFriends_List::AddFriend(CFriends *pFriend)
{
	if(m_Friends_List.size()>=m_nMaxFriends)
	{
		delete pFriend ;

		return false ;
	}

	m_Friends_List.push_back(pFriend) ;
	m_Friends_BeRelease.push_back(false) ;

	return true ;
}

void CFriends_List::SetMaxFriends(int nMaxFriends)
{
	m_nMaxFriends = nMaxFriends ;

	if(nMaxFriends<m_nMaxFriends)
	{
		std::vector<CFriends*> temp ;
		std::vector<bool> temp2 ;
		const int size = m_Friends_List.size() ;
		for(int i=0; i<size; i++)
		{
			temp.push_back(m_Friends_List.front()) ;
			m_Friends_List.erase(m_Friends_List.begin()) ;
		}

		Clear() ;

		m_Friends_List.swap(temp) ;

		m_Friends_BeRelease.erase(m_Friends_BeRelease.begin()+nMaxFriends, m_Friends_BeRelease.end()) ;
	}
}

void CFriends_List::Clear()
{
	CFriends *temp ;
	const int size = m_Friends_List.size() ;

	for(int i=0; i<size; i++)
	{
		temp = m_Friends_List[i] ;
		delete temp ;
	}

	if(!m_Friends_List.empty())
		m_Friends_List.clear() ;

	if(!m_Friends_BeRelease.empty())
		m_Friends_BeRelease.clear() ;
}

void CFriends_List::Gravity()
{
	CFriends *pFriend ;
	const int size = m_Friends_List.size() ;

	for(int i=0; i<size; i++)
	{
		pFriend = m_Friends_List[i] ;
		if(pFriend->GetRelease())
			pFriend->Gravity() ;
	}
}

void CFriends_List::ReleaseCheck()
{
	CFriends *pFriend ;
	bool bRelease ;
	const int size = m_Friends_List.size() ;

	for(int i=0; i<size; i++)
	{
		pFriend = m_Friends_List[i] ;
		bRelease = pFriend->GetRelease() ;

		if(m_Friends_BeRelease[i]!=bRelease)
		{
			m_Friends_BeRelease[i] = bRelease ;
			if(bRelease)
				g_DynamicObjects_List->AddObjects(pFriend) ;
			else
				g_DynamicObjects_List->RemoveObjects(pFriend) ;
		}
	}
}

void CFriends_List::Render()
{
	CFriends *pFriend ;
	const int size = m_Friends_List.size() ;

	for(int i=0; i<size; i++)
	{
		pFriend = m_Friends_List[i] ;
		if(pFriend->GetRelease())
			pFriend->Render() ;
	}
}

bool Compare(CFriends* pF1, CFriends* pF2)
{
	return pF1->GetPositionY() < pF2->GetPositionY() ;
}