#pragma once

#include "Sprite.h"

class CScrollBackground : public CSprite
{
private :
	float m_fScrollX, m_fScrollY ;
	float m_fScrollSpeedX, m_fScrollSpeedY ;

public :
	CScrollBackground() ;
	~CScrollBackground() ;

	void SetScrollSpeed(float fScrollSpeedX, float fScrollSpeedY) ;

	void Scroll() ;
} ;