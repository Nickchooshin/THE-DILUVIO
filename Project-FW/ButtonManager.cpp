#include "ButtonManager.h"
#include "Button.h"

#include "Mouse.h"

CButtonManager::CButtonManager()
{
}
CButtonManager::~CButtonManager()
{
	DeleteAllButtons() ;
}

void CButtonManager::AddButton(CButton *pButton)
{
	m_ButtonList.push_back(pButton) ;
}

void CButtonManager::DeleteButton(CButton *pButton)
{
	const int num=m_ButtonList.size() ;

	for(int i=0; i<num; i++)
	{
		if(m_ButtonList[i]==pButton)
		{
			delete m_ButtonList[i] ;
			m_ButtonList.erase(m_ButtonList.begin() + i) ;
			break ;
		}
	}
}

void CButtonManager::DeleteAllButtons()
{
	const int num=m_ButtonList.size() ;

	for(int i=0; i<num; i++)
		delete m_ButtonList[i] ;

	if(!m_ButtonList.empty())
		m_ButtonList.clear() ;
}

void CButtonManager::Update()
{
	const int num=m_ButtonList.size() ;
	int x=g_Mouse->GetMousePoint().x, y=g_Mouse->GetMousePoint().y ;
	bool bClick = g_Mouse->IsMouse(g_Mouse->LBUTTON_DOWN) ;
	bool bPress = g_Mouse->IsMousePress(g_Mouse->LBUTTON_UP) ;

	for(int i=0; i<num; i++)
		m_ButtonList[i]->ClickState(x, y, bClick, bPress) ;
}

/*void CButtonManager::Render()
{
	const int num=m_ButtonList.size() ;

	for(int i=0; i<num; i++)
		m_ButtonList[i]->Render() ;
}*/