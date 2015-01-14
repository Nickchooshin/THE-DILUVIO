#pragma once

#include "Singleton.h"
#include <vector>

class CButton ;

class CButtonManager : public Singleton<CButtonManager>
{
private :
	std::vector<CButton*> m_ButtonList ;

public :
	CButtonManager() ;
	~CButtonManager() ;

	void AddButton(CButton *pButton) ;
	void DeleteButton(CButton *pButton) ;
	void DeleteAllButtons() ;

	void Update() ;

	//void Render() ;
} ;

#define g_ButtonManager CButtonManager::GetInstance()