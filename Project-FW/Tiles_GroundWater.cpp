#include "Tiles_GroundWater.h"
#include "Sprite.h"

#include "DynamicObjects.h"

CTiles_GroundWater::CTiles_GroundWater()
{
}
CTiles_GroundWater::~CTiles_GroundWater()
{
}

void CTiles_GroundWater::Init()
{
	LoadDat("Resource/Data/Tiles/Ground_water.dat") ;
}

void CTiles_GroundWater::Effect1(CDynamicObjects* pDynamicObject)
{
	pDynamicObject->SetGravityMultiples(0.5f) ;
	//pDynamicObject->SetDeath(true) ;
}