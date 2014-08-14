#pragma once

#include "Tiles.h"

class CEffect_SparkArea ;

class CTiles_Spark : public CTiles
{
private :
	CEffect_SparkArea *m_pESparkArea ;
	Size m_AreaImgSize ;

public :
	CTiles_Spark() ;
	~CTiles_Spark() ;

	void Init() ;

	void Update() ;
	void Effect2(CDynamicObjects* pDynamicObject) ;

	void Render() ;
private :
	void Animation() ;
} ;