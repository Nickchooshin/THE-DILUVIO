#pragma once

#include <Windows.h>

class CSprite ;

class CObjects
{
protected :
	CSprite *m_pSprite ;
	float m_fX, m_fY ;
	RECT m_BoundingBox ;

public :
	CObjects() ;
	virtual ~CObjects() ;

	virtual void Init() = 0 ;

	void SetPosition(float fX, float fY) ;

	RECT GetBoundingBox() ;

	virtual void Render() ;
protected :
	virtual void SetBoundingBox() = 0 ;
} ;