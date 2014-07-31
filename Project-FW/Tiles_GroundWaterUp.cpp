#include "Tiles_GroundWaterUp.h"
#include "Sprite.h"

#include "DynamicObjects.h"

CTiles_GroundWaterUp::CTiles_GroundWaterUp()
{
}
CTiles_GroundWaterUp::~CTiles_GroundWaterUp()
{
}

void CTiles_GroundWaterUp::Init()
{
	LoadDat("Resource/Data/Tiles/Ground_water_up.dat") ;
}

void CTiles_GroundWaterUp::Effect1(CDynamicObjects* pDynamicObject)
{
	pDynamicObject->SetGravityMultiples(0.5f) ;
	//pDynamicObject->SetDeath(true) ;
}