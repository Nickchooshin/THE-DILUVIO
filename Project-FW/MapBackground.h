#pragma once

#include <vector>

class CSprite ;

class CMapBackground
{
private :
	std::vector<CSprite*> m_MapBackground_List ;
	std::vector<float> m_MapBackgroundX_List ;
	int m_nSize ;
	bool m_bBrick ;

	float m_fMapWidth ;

public :
	CMapBackground() ;
	~CMapBackground() ;

	void Init() ;

	void Scroll() ;

	void Render() ;
private :
	void Clear() ;
} ;