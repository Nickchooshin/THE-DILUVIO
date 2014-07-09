#pragma once

#include "Objects.h"

class CFriends : public CObjects
{
public :
	CFriends() {}
	virtual ~CFriends() {}

protected :
	void SetBoundingBox()
	{
		m_BoundingBox.left = -32 ;
		m_BoundingBox.top = 32 ;
		m_BoundingBox.right = 32 ;
		m_BoundingBox.bottom = -32 ;
	}
} ;