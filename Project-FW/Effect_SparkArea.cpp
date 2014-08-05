#include "Effect_SparkArea.h"

CEffect_SparkArea::CEffect_SparkArea()
{
}
CEffect_SparkArea::~CEffect_SparkArea()
{
}

void CEffect_SparkArea::Init()
{
	LoadDat("Resource/Data/Effect/Spark_ability.dat") ;
}

void CEffect_SparkArea::Effect(CObjects* pObject)
{
	pObject->SendEventMessage("SPARK") ;
}