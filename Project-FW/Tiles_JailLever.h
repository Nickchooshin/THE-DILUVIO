#pragma once

#include "Tiles.h"

class CTiles_JailLever : public CTiles
{
private :
	Position m_LinkIndex ;

public :
	CTiles_JailLever() ;
	~CTiles_JailLever() ;

	void Init() ;

	void Effect1(CDynamicObjects* pDynamicObject) ;
private :
	void Animation() ;
} ;