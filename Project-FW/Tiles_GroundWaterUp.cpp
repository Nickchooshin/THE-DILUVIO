#include "Tiles_GroundWaterUp.h"
#include "Sprite.h"
#include "DynamicObjects.h"

#include "D3dDevice.h"

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