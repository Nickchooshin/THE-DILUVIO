#pragma once

#include "Friends.h"

class CEffect_BusxoAbility ;

class CFriends_Busxo : public CFriends
{
private :
	CEffect_BusxoAbility *m_pEAbility ;

	int m_nStartEatFrame, m_nEatingFrame, m_nEndEatFrame ;
	Position m_Start_Eat_Index ;
	Position m_Eating_Index ;
	Position m_End_Eat_Index ;

	enum Ability_State { NONE=0, START_EAT, EATING, END_EAT } ;
	Ability_State m_AState, m_prevAState ;

public :
	CFriends_Busxo() ;
	~CFriends_Busxo() ;

	void Init() ;

	void Absorb() ;

	void Update() ;
private :
	void LoadBusxoDat() ;

	void Animation() ;
} ;