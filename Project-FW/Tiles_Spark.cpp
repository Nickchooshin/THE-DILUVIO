#include "Tiles_Spark.h"
#include "Effect_SparkArea.h"
#include "Sprite.h"

#include "Effect_List.h"

CTiles_Spark::CTiles_Spark() : m_pESparkArea(0)
{
}
CTiles_Spark::~CTiles_Spark()
{
	if(m_pESparkArea!=0)
		delete m_pESparkArea ;
}

void CTiles_Spark::Init()
{
	LoadDat("Resource/Data/Tiles/Spark.dat") ;

	m_pESparkArea = new CEffect_SparkArea ;
	m_pESparkArea->Init() ;

	g_Effect_List->AddEffect(m_pESparkArea) ;
}

void CTiles_Spark::Update()
{
	Animation() ;

	m_pESparkArea->Update() ;
}

void CTiles_Spark::Effect2()
{
}

void CTiles_Spark::Render()
{
	m_pSprite->SetPosition(m_fX, m_fY) ;
	m_pSprite->Render() ;

	m_pESparkArea->SetPosition(m_fX, m_fY) ;
	m_pESparkArea->Render() ;
}