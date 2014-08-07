#pragma once

#include "Singleton.h"
#include <vector>

class CFriends ;

class CFriends_List : public Singleton<CFriends_List>
{
private :
	std::vector<CFriends*> m_Friends_List ;
	std::vector<bool> m_Friends_BeRelease ;
	int m_nMaxFriends ;

public :
	CFriends_List() ;
	~CFriends_List() ;

	const int GetSize() ;

	CFriends* GetFriend(int index) ;
	CFriends* GetFriend(int tileX, int tileY) ;

	bool AddFriend(CFriends* pFriend) ;
	void SetMaxFriends(int nMaxFriends) ;
	void Clear() ;

	void Gravity() ;

	void ReleaseCheck() ;

	void Render() ;
} ;

#define g_Friends_List CFriends_List::GetInstance()