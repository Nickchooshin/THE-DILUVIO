#pragma once

#include "Objects.h"

class CTiles : public CObjects
{
public :
	CTiles() {}
	virtual ~CTiles() {}

protected :
	void SetBoundingBox()
	{
		m_BoundingBox.left = -32 ;
		m_BoundingBox.top = 32 ;
		m_BoundingBox.right = 32 ;
		m_BoundingBox.bottom = -32 ;
	}
} ;