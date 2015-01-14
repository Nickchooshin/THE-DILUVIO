#include "ScrollBackground.h"
#include "D3dDevice.h"

CScrollBackground::CScrollBackground() : m_fScrollX(0.0f), m_fScrollY(0.0f),
										 m_fScrollSpeedX(0.0f), m_fScrollSpeedY(0.0f)
{
}
CScrollBackground::~CScrollBackground()
{
}

void CScrollBackground::SetScrollSpeed(float fScrollSpeedX, float fScrollSpeedY)
{
	m_fScrollSpeedX = fScrollSpeedX ;
	m_fScrollSpeedY = fScrollSpeedY ;
}

void CScrollBackground::Scroll()
{
	float fMoveTime = g_D3dDevice->GetMoveTime() ;

	m_fScrollX += m_fScrollSpeedX * fMoveTime ;
	m_fScrollY += m_fScrollSpeedY * fMoveTime ;

	if(m_fScrollX>m_pTexInfo->Width)
		m_fScrollX -= m_pTexInfo->Width ;
	else if(m_fScrollX<0)
		m_fScrollX += m_pTexInfo->Width ;

	if(m_fScrollY>m_pTexInfo->Height)
		m_fScrollY -= m_pTexInfo->Height ;
	else if(m_fScrollY<0)
		m_fScrollY += m_pTexInfo->Height ;

	SetTextureUV(m_fScrollX, m_fScrollY, (m_fScrollX + m_fWidth), (m_fScrollY + m_fHeight)) ;
}