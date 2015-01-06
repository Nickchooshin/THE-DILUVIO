#pragma once

#include "Friends.h"

class CEffect_RanchoEat ;

class CFriends_Rancho : public CFriends
{
private :
	CEffect_RanchoEat *m_pEAbilityL, *m_pEAbilityR ;

	int m_nEatFrame ;
	Position m_Eat_Index ;

	enum Ability_State { NONE=0, EAT } ;
	Ability_State m_AState, m_prevAState ;

public :
	CFriends_Rancho() ;
	~CFriends_Rancho() ;

	void Init() ;

	void Update() ;

	virtual void SendEventMessage(char *EventMessage, void *pData) ;

	void Render() ;
private :
	void Eat(int x, int y, char cDirection) ;
	
	void LoadRanchoDat() ;

	void Animation() ;
} ;