#include "Tiles.h"
#include "Sprite.h"
#include "LoadManager.h"

#include "D3dDevice.h"

CTiles::CTiles() : m_ImgSize(0, 0), m_ColSize(0, 0),
				   m_nNowFrame(0),
				   m_nTileFrame(0), m_nEffectFrame(0),
				   m_Tile_Index(0, 0),
				   m_Effect_Index(0, 0),
				   m_pLinkedTile(NULL),
				   m_bCollision(true),
				   m_fAnimationTime(0.0f),
				   m_State(NORMAL), m_prevState(NORMAL),
				   m_CollisionDirection(0)
{
}
CTiles::~CTiles()
{
}

void CTiles::Update()
{
	Animation() ;

	m_CollisionDirection = 0 ;
}

void CTiles::Effect()
{
}

void CTiles::SetLinkedTile(CTiles *pLinkedTile)
{
	m_pLinkedTile = pLinkedTile ;
}

void CTiles::SetCollision(bool bFlag)
{
	m_bCollision = bFlag ;
}

const bool CTiles::BeCollision()
{
	return m_bCollision ;
}

void CTiles::CollisionDirection(int direction)
{
	m_CollisionDirection |= direction ;
}

void CTiles::LoadDat(char *filepath)
{
	g_LoadManager->OpenDat(filepath) ;

	char item[100] ;
	char image_path[100] ;

	while(g_LoadManager->GetItem(item))
	{
		if(strcmp(item, "IMAGE")==0)
		{
			g_LoadManager->GetString(image_path) ;
		}
		else if(strcmp(item, "SIZE")==0)
		{
			g_LoadManager->GetValue(m_ImgSize.x) ;
			g_LoadManager->GetValue(m_ImgSize.y) ;
		}
		else if(strcmp(item, "EFFECT_ENABLE")==0)
		{
			char str[10] ;
			g_LoadManager->GetString(str) ;

			if(strcmp(str, "true")==0 || strcmp(str, "TRUE")==0)
				m_bCollision = false ;
			else if(strcmp(str, "false")==0 || strcmp(str, "FALSE")==0)
				m_bCollision = true ;
		}
		else if(strcmp(item, "COLLISION_BOX")==0)
		{
			g_LoadManager->GetValue(m_BoundingBox.left) ;
			g_LoadManager->GetValue(m_BoundingBox.top) ;
			g_LoadManager->GetValue(m_BoundingBox.right) ;
			g_LoadManager->GetValue(m_BoundingBox.bottom) ;
		}
		else if(strcmp(item, "TILE_FRAME")==0)
		{
			g_LoadManager->GetValue(m_nTileFrame) ;
		}
		else if(strcmp(item, "TILE_INDEX")==0)
		{
			g_LoadManager->GetValue(m_Tile_Index.x) ;
			g_LoadManager->GetValue(m_Tile_Index.y) ;
		}
		else if(strcmp(item, "EFFECT_FRAME")==0)
		{
			g_LoadManager->GetValue(m_nEffectFrame) ;
		}
		else if(strcmp(item, "EFFECT_INDEX")==0)
		{
			g_LoadManager->GetValue(m_Effect_Index.x) ;
			g_LoadManager->GetValue(m_Effect_Index.y) ;
		}
	}

	g_LoadManager->CloseDat() ;

	m_pSprite = new CSprite ;
	m_pSprite->Init((float)m_ImgSize.x, (float)m_ImgSize.y, image_path) ;
	m_pSprite->SetTextureUV((float)(m_Tile_Index.x * m_ImgSize.x), (float)(m_Tile_Index.y * m_ImgSize.y),
							(float)((m_Tile_Index.x+1) * m_ImgSize.x), (float)((m_Tile_Index.y+1) * m_ImgSize.y)) ;

	SetBoundingBox() ;
}

void CTiles::SetBoundingBox()
{
	m_BoundingBox.left = -(m_ImgSize.x/2) + m_BoundingBox.left ;
	m_BoundingBox.top = (m_ImgSize.y/2) - m_BoundingBox.top ;
	m_BoundingBox.right = m_BoundingBox.right - (m_ImgSize.x/2) ;
	m_BoundingBox.bottom = -m_BoundingBox.bottom + (m_ImgSize.y/2) ;
}

void CTiles::Animation()
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

	case EFFECT :
		MaxFrame = m_nEffectFrame ;
		Index = m_Effect_Index ;
		break ;
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
			m_nNowFrame = 0 ;
			m_State = NORMAL ;
		}
		m_nNowFrame %= MaxFrame ;
	}

	m_prevState = m_State ;
}