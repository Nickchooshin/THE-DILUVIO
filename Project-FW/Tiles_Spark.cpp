#include "Tiles_Spark.h"
#include "Effect_SparkArea.h"
#include "Sprite.h"

#include "Effect_List.h"

#include "D3dDevice.h"

CTiles_Spark::CTiles_Spark() : m_pESparkArea(NULL)
{
}
CTiles_Spark::~CTiles_Spark()
{
	if(m_pESparkArea!=NULL)
		delete m_pESparkArea ;
}

void CTiles_Spark::Init()
{
	LoadDat("Resource/Data/Tiles/Spark.dat") ;

	m_pESparkArea = new CEffect_SparkArea ;
	m_pESparkArea->Init() ;
	m_pESparkArea->SetVisible(true) ;

	g_Effect_List->AddEffect(m_pESparkArea) ;
}

void CTiles_Spark::Update()
{
	if(m_bCollision==false)
		return ;

	if(m_bUnVisible)
	{
		m_bUnVisible = false ;
		m_bCollision = false ;
		return ;
	}

	Animation() ;
	
	//m_pESparkArea->SetVisible(true) ;
	m_pESparkArea->SetPosition(m_fX, m_fY) ;
	m_pESparkArea->Update() ;
}

void CTiles_Spark::Effect2(CDynamicObjects* pDynamicObject)
{
	m_State = EFFECT2 ;
	m_pESparkArea->SetVisible(false) ;
}

void CTiles_Spark::Render()
{
	if(m_bCollision==false)
		return ;

	m_pSprite->SetPosition(m_fX, m_fY) ;
	m_pSprite->Render() ;

	m_pESparkArea->SetPosition(m_fX, m_fY) ;
	m_pESparkArea->Render() ;
}

void CTiles_Spark::Animation()
{
	// Animation Frame, Index
	int MaxFrame ;
	Position Index ;

	switch(m_State)
	{
	case NORMAL :
		MaxFrame = m_nTileFrame ;
		Index = m_Tile_Index ;
		break ;

	case EFFECT1 :
		MaxFrame = m_nEffect1Frame ;
		Index = m_Effect1_Index ;
		break ;

	case EFFECT2 :
		MaxFrame = m_nEffect2Frame ;
		Index = m_Effect2_Index ;
	}

	// Animation
	m_fAnimationTime += g_D3dDevice->GetTime() ;

	if(m_fAnimationTime>=0.2f || (m_State!=m_prevState))
	{
		if(m_State!=m_prevState)
		{
			m_nNowFrame = 0 ;
			m_fAnimationTime = 0.0f ;
		}

		float left, top, right, bottom ;
		left = (float)((Index.x + m_nNowFrame) * m_ImgSize.x) ;
		top = (float)((Index.y) * m_ImgSize.y) ;
		right = (float)((Index.x + m_nNowFrame+1) * m_ImgSize.x) ;
		bottom = (float)((Index.y+1) * m_ImgSize.y) ;

		m_pSprite->SetTextureUV(left, top, right, bottom) ;

		int Frame = (int)(m_fAnimationTime / 0.2f) ;
		m_fAnimationTime -= Frame * 0.2f ;
		Frame %= MaxFrame ;
		m_nNowFrame += Frame ;
		if(m_nNowFrame>=MaxFrame)
		{
			if(m_State==EFFECT2)
				m_bUnVisible = true ;
			m_nNowFrame = 0 ;
			m_State = NORMAL ;
		}
	}

	m_prevState = m_State ;
}