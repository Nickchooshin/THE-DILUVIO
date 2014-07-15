#pragma once

#include "Singleton.h"
#include <vector>

class CFriends ;

class CFriends_List : public Singleton<CFriends_List>
{
private :
	std::vector<CFriends*> m_Friends_List ;
	int m_nMaxFriends ;

public :
	CFriends_List() ;
	~CFriends_List() ;

	const int GetSize() ;

	bool AddFriend(CFriends* pFriends) ;
	void SetMaxFriends(int nMaxFriends) ;
	void Clear() ;

	CFriends* GetFriend(int index) ;
} ;

#define g_Friends_List CFriends_List::GetInstance()