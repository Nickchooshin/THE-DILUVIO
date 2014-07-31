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