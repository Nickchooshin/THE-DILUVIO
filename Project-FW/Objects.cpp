#include "Objects.h"
#include "Sprite.h"

CObjects::CObjects() : m_pSprite(NULL),
					   m_fX(0.0f), m_fY(0.0f),
					   m_bUnVisible(false)
{
}
CObjects::~CObjects()
{
	if(m_pSprite!=NULL)
		delete m_pSprite ;
}

const float CObjects::GetPositionX()
{
	return m_fX ;
}

const float CObjects::GetPositionY()
{
	return m_fY ;
}

void CObjects::SetPosition(float fX, float fY)
{
	m_fX = fX ;
	m_fY = fY ;
}

const Rect CObjects::GetBoundingBox()
{
	Rect rt ;
	rt.left = m_BoundingBox.left + (int)m_fX ;
	rt.top = m_BoundingBox.top + (int)m_fY ;
	rt.right = m_BoundingBox.right + (int)m_fX ;
	rt.bottom = m_BoundingBox.bottom + (int)m_fY ;

	return rt ;
}

void CObjects::Render()
{
	m_pSprite->SetPosition(m_fX, m_fY) ;
	m_pSprite->Render() ;
}

//
void CObjects::SendEventMessage(char *EventMessage, void *pData)
{
}

void CObjects::EventClear()
{
}