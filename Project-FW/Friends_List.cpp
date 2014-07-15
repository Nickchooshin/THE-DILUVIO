#include "Friends_List.h"
#include "Friends.h"

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



	//
	if(nMaxFriends<m_nMaxFriends)
	{
		std::vector<CFriends*> temp ;
		const int size = m_Friends_List.size() ;
		for(int i=0; i<size; i++)
		{
			temp.push_back(m_Friends_List.front()) ;
			//m_Friends_List.pop_front() ;
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

CFriends* CFriends_List::GetFriend(int index)
{
	/*index %= m_Friends_List.size() ;

	for(int i=0; i<index; i++)
	{
	}*/

	const int size = m_Friends_List.size() ;

	if(size==0)
		return NULL ;
	else if(index<0)
		//index += size ;
		index = (size - ((size - index) % size)) % size ;
	else if(index>=size)
		index %= size ;

	return m_Friends_List[index] ;
}