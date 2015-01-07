#pragma once

#include "Friends.h"

class CFriends_Mano : public CFriends
{
private :
	int m_nFaintFrame ;
	Position m_Stand_RightIndex ;
	Position m_Absorb_RightIndex ;
	Position m_Release_RightIndex ;
	Position m_Stun_RightIndex ;
	Position m_Faint_LeftIndex, m_Faint_RightIndex ;

	Direction m_Direction ;
	
	enum Ability_State { NONE=0, FAINT } ;
	Ability_State m_AState, m_prevAState ;

public :
	CFriends_Mano() ;
	~CFriends_Mano() ;

	void Init() ;

	void Release() ;

	void SendEventMessage(char *EventMessage, void *pData) ;

	void Update() ;
private :
	void Faint(int x, int y, char cDirection) ;

	void LoadManoDat() ;

	void Animation() ;
} ;