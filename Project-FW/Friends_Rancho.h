#pragma once

#include "Friends.h"

class CEffect_RanchoEat ;

class CFriends_Rancho : public CFriends
{
private :
	CEffect_RanchoEat *m_pEAbilityL, *m_pEAbilityR ;

public :
	CFriends_Rancho() ;
	~CFriends_Rancho() ;

	void Init() ;

	void Update() ;

	virtual void SendEventMessage(char *EventMessage, void *pData) ;

	void Render() ;
private :
	void Eat(int x, int y, char cDirection) ;
} ;