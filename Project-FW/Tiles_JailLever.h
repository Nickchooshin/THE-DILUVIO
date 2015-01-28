#pragma once

#include "Tiles.h"
#include <fmod.hpp>

class CTiles_JailLever : public CTiles
{
private :
	Position m_LinkIndex ;

	FMOD::Sound *m_pSELever ;

public :
	CTiles_JailLever() ;
	~CTiles_JailLever() ;

	void Init() ;

	void Effect1(CDynamicObjects* pDynamicObject) ;
private :
	void Animation() ;
} ;