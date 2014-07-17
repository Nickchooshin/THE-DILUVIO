#pragma once

#include "Singleton.h"
#include <vector>

class CFriends ;

class CFriends_List : public Singleton<CFriends_List>
{
private :
	std::vector<CFriends*> m_Friends_List ;
	std::vector<CFriends*> m_CollisionList ;
	int m_nMaxFriends ;

public :
	CFriends_List() ;
	~CFriends_List() ;

	const int GetSize() ;

	CFriends* GetFriend(int index) ;

	bool AddFriend(CFriends* pFriends) ;
	void SetMaxFriends(int nMaxFriends) ;
	void Clear() ;

	void Gravity() ;

	void Update() ;

	void Render() ;

	void Collision() ;
} ;

#define g_Friends_List CFriends_List::GetInstance()