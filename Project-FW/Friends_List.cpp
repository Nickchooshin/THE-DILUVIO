#include "Friends_List.h"
#include "Friends.h"

#include <algorithm>
#include "Collision.h"

#include "Hero.h"

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
	CFriends *pFriends ;
	std::vector<CFriends*>::iterator iter ;
	std::vector<CFriends*>::iterator end=m_Friends_List.end() ;

	for(iter=m_Friends_List.begin(); iter!=end; iter++)
	{
		pFriends = *iter ;

		if(pFriends->GetRelease())
		{
			int x = (int)((pFriends->GetPositionX() + 32.0f) / 64.0f) ;
			int y = (int)((pFriends->GetPositionY() + 32.0f) / 64.0f) ;

			if(tileX==x && tileY==y)
				return pFriends ;
		}
	}

	return NULL ;
}

bool CFriends_List::AddFriend(CFriends *pFriends)
{
	if(m_Friends_List.size()>=m_nMaxFriends)
	{
		delete pFriends ;

		return false ;
	}

	m_Friends_List.push_back(pFriends) ;
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
	std::vector<CFriends*>::iterator iter ;
	std::vector<CFriends*>::iterator end=m_Friends_List.end() ;

	for(iter=m_Friends_List.begin(); iter!=end; iter++)
	{
		temp = *iter ;
		delete temp ;
	}

	m_Friends_List.clear() ;

	m_Friends_BeRelease.clear() ;
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

void CFriends_List::ReleaseCheck()
{
	int count=0 ;
	bool bRelease ;
	CFriends *pFriends ;
	std::vector<CFriends*>::iterator iter ;
	std::vector<CFriends*>::iterator end=m_Friends_List.end() ;

	for(iter=m_Friends_List.begin(); iter!=end; iter++, count++)
	{
		pFriends = *iter ;
		bRelease = pFriends->GetRelease() ;

		if(m_Friends_BeRelease[count]!=bRelease)
		{
			m_Friends_BeRelease[count] = bRelease ;
			if(bRelease)
				g_DynamicObjects_List->AddObjects(pFriends) ;
			else
				g_DynamicObjects_List->RemoveObjects(pFriends) ;
		}
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

//void CFriends_List::Collision(char coord)
//{
//	std::sort(m_CollisionList.begin(), m_CollisionList.end(), Compare) ;
//	
//	CCollision col ;
//	int size = m_CollisionList.size() ;
//
//	for(int i=0; i<size; i++)
//	{
//		for(int j=0; j<size; j++)
//		{
//			if(i==j)
//				continue ;
//
//			if(coord=='x' || coord=='X')
//				col.XCollision(m_CollisionList[j], m_CollisionList[i]) ;
//			else if(coord=='y' || coord=='Y')
//				col.YCollision(m_CollisionList[j], m_CollisionList[i]) ;
//		}
//	}
//
//	m_CollisionList.clear() ;
//}
//
//void CFriends_List::Collision(CHero *pHero, char coord)
//{
//	CFriends *pFriends ;
//	std::vector<CFriends*>::iterator iter ;
//	std::vector<CFriends*>::iterator end=m_Friends_List.end() ;
//
//	CCollision col ;
//
//	for(iter=m_Friends_List.begin(); iter!=end; iter++)
//	{
//		pFriends = *iter ;
//		if(!pFriends->GetRelease())
//			continue ;
//
//		if(coord=='x' || coord=='X')
//			col.XCollision(pHero, pFriends) ;
//		else if(coord=='y' || coord=='Y')
//			col.YCollision(pHero, pFriends) ;
//	}
//}