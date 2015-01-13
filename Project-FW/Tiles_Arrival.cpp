#include "Tiles_Arrival.h"
#include "DynamicObjects.h"

CTiles_Arrival::CTiles_Arrival()
{
}
CTiles_Arrival::~CTiles_Arrival()
{
}

void CTiles_Arrival::Init()
{
	LoadDat("Resource/Data/Tiles/Arrival.dat") ;
}

void CTiles_Arrival::Effect1(CDynamicObjects* pDynamicObject)
{
	pDynamicObject->SendEventMessage("ARRIVAL") ;
}