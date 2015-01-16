#include "Button.h"
#include "Sprite.h"

#include "Mouse.h"
#include "TextureManager.h"

#include "MusicManager.h"

CButton::CButton() : m_fX(0.0f), m_fY(0.0f),
					 m_fWidth(0.0f), m_fHeight(0.0f),
					 m_nState(0), m_nPrevState(-1),
					 m_bActivate(true), m_bClick(false), m_bPuton(false), m_bPutonActivate(false),
					 m_bVisible(true),
					 m_pSprite(NULL),
					 m_pClickDown(NULL), m_pClickUp(NULL), m_pPuton(NULL)
{
	for(int i=0; i<4; i++)
		m_nIndex[i] = 0 ;
}
CButton::~CButton()
{
	if(m_pSprite!=NULL)
		delete m_pSprite ;
}

void CButton::Init(char *texfile)
{
	m_pSprite = new CSprite ;
	m_pSprite->Init(texfile) ;

	D3DXIMAGE_INFO TexInfo = g_TextureManager->GetTexInfo(texfile) ;
	m_fWidth = (float)TexInfo.Width ;
	m_fHeight = (float)TexInfo.Height ;
}

void CButton::Init(float Width, float Height, char *texfile)
{
	m_pSprite = new CSprite ;
	m_pSprite->Init(Width, Height, texfile) ;

	m_fWidth = Width ;
	m_fHeight = Height ;
}

void CButton::SetPosition(float fX, float fY)
{
	m_fX = fX ;
	m_fY = fY ;
}

void CButton::SetIndex(int normalIndex, int putonIndex, int clickIndex, int disableIndex)
{
	m_nIndex[0] = normalIndex ;
	m_nIndex[1] = putonIndex ;
	m_nIndex[2] = clickIndex ;
	m_nIndex[3] = disableIndex ;
}

void CButton::SetActivate(bool bActivate)
{
	m_bActivate = bActivate ;
}

void CButton::SetVisible(bool bVisible)
{
	m_bVisible = bVisible ;
}

void CButton::SetPutonActivate(bool bActivate)
{
	m_bPutonActivate = bActivate ;
}

void CButton::SetClickDownSound(char *filepath)
{
	m_pClickDown = g_MusicManager->LoadMusic(filepath, false, false) ;
}

void CButton::SetClickUpSound(char *filepath)
{
	m_pClickUp = g_MusicManager->LoadMusic(filepath, false, false) ;
}

void CButton::SetPutonSound(char *filepath)
{
	m_pPuton = g_MusicManager->LoadMusic(filepath, false, false) ;
}

void CButton::SetAlpha(int nAlpha)
{
	m_pSprite->SetAlpha(nAlpha) ;
}

void CButton::ClickState(int x, int y, bool bClick, bool bPress)
{
	m_bClick = false ;
	m_bPuton = false ;
	if(!m_bActivate || !m_bVisible)
		return ;

	if(bPress && CollisionCheck(x, y))
	{
		if(m_pClickDown!=NULL)
			g_MusicManager->PlayMusic(m_pClickDown, 1) ;
		m_bClick = true ;
	}
	else if(bClick && CollisionCheck(x, y))
	{
		if(m_nState!=m_nIndex[2] && m_pClickUp!=NULL)
			g_MusicManager->PlayMusic(m_pClickUp, 1) ;
		m_nState = m_nIndex[2] ;
	}
	else if(m_bPutonActivate && CollisionCheck(x, y))
	{
		if(m_nState!=m_nIndex[1] && m_pPuton!=NULL)
			g_MusicManager->PlayMusic(m_pPuton, 1) ;
		m_nState = m_nIndex[1] ;
		m_bPuton = true ;
	}
	else
	{
		m_nState = m_nIndex[0] ;
	}
}

const bool CButton::BeClick() const
{
	return m_bClick ;
}

const bool CButton::BePuton() const
{
	return m_bPuton ;
}

const bool CButton::BeActivate() const
{
	return m_bActivate ;
}

const bool CButton::BeVisible() const
{
	return m_bVisible ;
}

void CButton::Render()
{
	if(!m_bVisible)
		return ;

	if(!m_bActivate)
		m_nState = m_nIndex[3] ;

	if(m_nState!=m_nPrevState)
	{
		m_pSprite->SetTextureUV((m_nState * m_fWidth), 0.0f, ((m_nState+1) * m_fWidth), m_fHeight) ;
		m_nPrevState = m_nState ;
	}

	m_pSprite->SetPosition(m_fX, m_fY) ;
	m_pSprite->Render() ;
}

bool CButton::CollisionCheck(int x, int y)
{
	float widthHalf = m_fWidth/2.0f ;
	float heightHalf = m_fHeight/2.0f ;

	if( (x>=(m_fX-widthHalf) && x<=(m_fX+widthHalf)) &&
		(y>=(m_fY-heightHalf) && y<=(m_fY+heightHalf)) )
	{
		return true ;
	}

	return false ;
}