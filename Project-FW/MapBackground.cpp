#include "MapBackground.h"
#include "Sprite.h"

#include "MapTiles_List.h"
#include "StageProgress.h"

#include "D3dDevice.h"

CMapBackground::CMapBackground() : m_nSize(0),
								   m_bBrick(false),
								   m_fMapWidth(0.0f)
{
}
CMapBackground::~CMapBackground()
{
	Clear() ;
}

void CMapBackground::Init()
{
	int WinWidth = g_D3dDevice->GetWinWidth() ;
	int WinHeight = g_D3dDevice->GetWinHeight() ;
	Size MapSize = g_MapTiles_List->GetMapSize() ;
	Size BackgroundSize ;

	MapSize.x *= 64 ;
	MapSize.y *= 64 ;

	BackgroundSize.x = MapSize.x / WinWidth ;
	BackgroundSize.y = MapSize.y / WinHeight ;

	m_bBrick = (g_StageProgress->GetSelectChapter() == 5) ;
	if(m_bBrick)
	{
		BackgroundSize.x *= 2 ;
		BackgroundSize.y *= 2 ;
	}

	if(MapSize.x%WinWidth!=0)
		BackgroundSize.x += 1 ;
	if(MapSize.y%WinHeight!=0)
		BackgroundSize.y += 1 ;

	CSprite *pSprite=NULL ;
	char filepath[1024] ;

	for(int i=0; i<BackgroundSize.y; i++)
	{
		for(int j=0; j<BackgroundSize.x; j++)
		{
			float fX, fY ;

			if(m_bBrick)
			{
				if(i==BackgroundSize.y-1)
					sprintf_s(filepath, "Resource/Image/Background/Background_Brick_Flag.png") ;
				else if(i==BackgroundSize.y-2)
					sprintf_s(filepath, "Resource/Image/Background/Background_Brick_Normal.png") ;
				else
					sprintf_s(filepath, "Resource/Image/Background/Background_Brick_Broken.png") ;

				fX = (float)((WinWidth / 2) * j) + (WinWidth / 4) - 32.0f ;
				fY = (float)((WinHeight / 2) * i) + (WinHeight / 4) - 32.0f ;
			}
			else
			{
				if(i==0)
					sprintf_s(filepath, "Resource/Image/Background/Background_Down%d.png", rand()%2+1) ;
				else
					sprintf_s(filepath, "Resource/Image/Background/Background_Up%d.png", rand()%3+1) ;
				
				fX = (float)(WinWidth * j) + (WinWidth / 2) - 32.0f ;
				fY = (float)(WinHeight * i) + (WinHeight / 2) - 32.0f ;
			}

			pSprite = new CSprite ;
			pSprite->Init(filepath) ;
			pSprite->SetPosition(fX, fY) ;

			m_MapBackground_List.push_back(pSprite) ;
			m_MapBackgroundX_List.push_back(fX) ;
		}
	}

	m_nSize = m_MapBackground_List.size() ;

	//m_fMapWidth = MapSize.x ;
	m_fMapWidth = BackgroundSize.x * WinWidth ;
}

void CMapBackground::Scroll()
{
	if(m_bBrick)
		return ;

	float fX ;
	float fWinWidthHalf = g_D3dDevice->GetWinWidth() / 2.0f ;
	float fScrollSpeed = g_D3dDevice->GetMoveTime() * -1.0f ;

	for(int i=0; i<m_nSize; i++)
	{
		fX = m_MapBackgroundX_List[i] + fScrollSpeed ;
		if(fX<(-fWinWidthHalf - 32.0f))
			fX += m_fMapWidth ;

		m_MapBackground_List[i]->SetPositionX(fX) ;
		m_MapBackgroundX_List[i] = fX ;
	}
}

void CMapBackground::Render()
{
	float fX ;
	float fWinWidthHalf = g_D3dDevice->GetWinWidth() / 2.0f ;

	CSprite *pSprite ;

	for(int i=0; i<m_nSize; i++)
	{
		pSprite = m_MapBackground_List[i] ;

		pSprite->Render() ;

		fX = m_MapBackgroundX_List[i] ;
		if(fX<(fWinWidthHalf - 32.0f))
		{
			pSprite->SetPositionX(fX + m_fMapWidth) ;
			pSprite->Render() ;
			pSprite->SetPositionX(fX) ;
		}
	}
}

void CMapBackground::Clear()
{
	if(m_MapBackground_List.empty())
		return ;

	for(int i=0; i<m_nSize; i++)
		delete m_MapBackground_List[i] ;

	m_MapBackground_List.clear() ;
	m_MapBackgroundX_List.clear() ;
}