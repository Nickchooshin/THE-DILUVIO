#pragma once

#include "Singleton.h"
#include <vector>

class CHero ;

class CFriends ;

class CFriends_List : public Singleton<CFriends_List>
{
private :
	std::vector<CFriends*> m_Friends_List ;
	std::vector<CFriends*> m_CollisionList ;
	std::vector<bool> m_Friends_BeRelease ;
	int m_nMaxFriends ;

public :
	CFriends_List() ;
	~CFriends_List() ;

	const int GetSize() ;

	CFriends* GetFriend(int index) ;
	CFriends* GetFriend(int tileX, int tileY) ;

	bool AddFriend(CFriends* pFriends) ;
	void SetMaxFriends(int nMaxFriends) ;
	void Clear() ;

	void Gravity() ;

	void ReleaseCheck() ;

	void Render() ;

	//void Collision() ;
	//
	//void Collision(char coord) ;
	//void Collision(CHero *pHero, char coord) ;
} ;

#define g_Friends_List CFriends_List::GetInstance()