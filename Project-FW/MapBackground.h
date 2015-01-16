#pragma once

#include <vector>

class CScrollBackground ;

class CMapBackground
{
private :
	std::vector<CScrollBackground*> m_MapBackground_List ;
	int m_nSize ;

public :
	CMapBackground() ;
	~CMapBackground() ;

	void Init() ;

	void Scroll() ;

	void Render() ;
private :
	void Clear() ;
} ;