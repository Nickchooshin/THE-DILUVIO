#pragma once

#include "Tiles.h"

class CTiles_Glass : public CTiles
{
private :
	bool m_bOkuloEffect ;
	bool m_bRecover ;
	bool m_bVisible ;

public :
	CTiles_Glass() ;
	~CTiles_Glass() ;

	void Init() ;

	void Update() ;

	void Render() ;

	void SendEventMessage(char *EventMessage) ;
	void EventClear() ;
private :
	void Animation() ;
} ;