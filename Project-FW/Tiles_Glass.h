#pragma once

#include "Tiles.h"
#include <fmod.hpp>

class CTiles_Glass : public CTiles
{
private :
	bool m_bOkuloEffect ;
	bool m_bRecover, m_bAbleRecover ;
	bool m_bVisible ;

	FMOD::Sound *m_pSEGlass ;

public :
	CTiles_Glass() ;
	~CTiles_Glass() ;

	void Init() ;

	void Update() ;
	void Effect1(CDynamicObjects* pDynamicObject) ;

	void Render() ;

	void SendEventMessage(char *EventMessage, void *pData) ;
	void EventClear() ;
private :
	void Animation() ;
} ;