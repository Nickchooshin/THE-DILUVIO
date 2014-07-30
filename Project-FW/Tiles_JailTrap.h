#pragma once

#include "Tiles.h"

class CTiles_JailTrap : public CTiles
{
private :
	bool m_bWork ;
	bool m_bDestory ;

public :
	CTiles_JailTrap() ;
	~CTiles_JailTrap() ;

	void Init() ;

	void Render() ;

	void Effect1() ;
	void Effect2() ;
private :
	void Animation() ;
} ;