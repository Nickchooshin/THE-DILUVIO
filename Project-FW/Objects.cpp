#include "Objects.h"
#include "Sprite.h"

CObjects::CObjects() : m_pSprite(NULL),
					   m_fX(0.0f), m_fY(0.0f)
{
}
CObjects::~CObjects()
{
	if(m_pSprite!=NULL)
		delete m_pSprite ;
}

void CObjects::SetPosition(float fX, float fY)
{
	m_fX = fX ;
	m_fY = fY ;
}

RECT CObjects::GetBoundingBox()
{
	RECT rt ;
	rt.left = m_BoundingBox.left + m_fX ;
	rt.top = m_BoundingBox.top + m_fY ;
	rt.right = m_BoundingBox.right + m_fX ;
	rt.bottom = m_BoundingBox.bottom + m_fY ;

	return rt ;
}

void CObjects::Render()
{
	m_pSprite->SetPosition(m_fX, m_fY) ;
	m_pSprite->Render() ;
}