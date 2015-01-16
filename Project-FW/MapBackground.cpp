#include "MapBackground.h"
#include "ScrollBackground.h"

#include "MapTiles_List.h"

#include "D3dDevice.h"

CMapBackground::CMapBackground()
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
	if(MapSize.x%WinWidth!=0)
		BackgroundSize.x += 1 ;
	if(MapSize.y%WinHeight!=0)
		BackgroundSize.y += 1 ;

	CScrollBackground *pScrollBackground=NULL ;
	char filepath[1024] ;

	for(int i=0; i<BackgroundSize.y; i++)
	{
		for(int j=0; j<BackgroundSize.x; j++)
		{
			if(i==0)
				sprintf_s(filepath, "Resource/Image/Background/Background_Down%d.png", rand()%2+1) ;
			else
				sprintf_s(filepath, "Resource/Image/Background/Background_Up%d.png", rand()%3+1) ;

			pScrollBackground = new CScrollBackground ;
			pScrollBackground->Init(filepath) ;
			pScrollBackground->SetPosition((float)(WinWidth * j) + (WinWidth / 2) - 32.0f, (float)(WinHeight * i) + (WinHeight / 2) - 32.0f) ;
			pScrollBackground->SetScrollSpeed(1.0f, 0.0f) ;

			m_MapBackground_List.push_back(pScrollBackground) ;
		}
	}

	m_nSize = m_MapBackground_List.size() ;
}

void CMapBackground::Scroll()
{
	for(int i=0; i<m_nSize; i++)
		m_MapBackground_List[i]->Scroll() ;
}

void CMapBackground::Render()
{
	for(int i=0; i<m_nSize; i++)
		m_MapBackground_List[i]->Render() ;
}

void CMapBackground::Clear()
{
	if(!m_MapBackground_List.empty())
		return ;

	for(int i=0; i<m_nSize; i++)
		delete m_MapBackground_List[i] ;

	m_MapBackground_List.clear() ;
}