#pragma once

#include "Tiles.h"

class CTiles_JailTrap : public CTiles
{
private :
	bool m_bWork ;
	bool m_bDestory ;
	bool m_bConfined ;

	CDynamicObjects *m_pTrappedObject ;
	int m_nPulledCount ;

public :
	CTiles_JailTrap() ;
	~CTiles_JailTrap() ;

	void Init() ;

	void Update() ;

	void Render() ;

	void Effect1(CDynamicObjects* pDynamicObject) ;
	void Effect2(CDynamicObjects* pDynamicObject) ;
private :
	void Animation() ;
} ;