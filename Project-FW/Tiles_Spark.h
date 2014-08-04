#pragma once

#include "Tiles.h"

class CEffect_SparkArea ;

class CTiles_Spark : public CTiles
{
private :
	CEffect_SparkArea *m_pESparkArea ;
	Size m_AreaImgSize ;
	int m_nTileFrame ;

public :
	CTiles_Spark() ;
	~CTiles_Spark() ;

	void Init() ;

	void Update() ;
	void Effect2() ;

	void Render() ;
} ;