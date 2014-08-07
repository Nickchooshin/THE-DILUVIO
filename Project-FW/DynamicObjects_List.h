#pragma once

#include "Singleton.h"
#include <vector>

class CDynamicObjects ;

class CDynamicObjects_List : public Singleton<CDynamicObjects_List>
{
private :
	CDynamicObjects *m_pMainChar ;
	std::vector<CDynamicObjects*> m_DynamicObjects_List ;

public :
	CDynamicObjects_List() ;
	~CDynamicObjects_List() ;

	void AddMainCharObjects(CDynamicObjects *pDynamicObject) ;
	void AddObjects(CDynamicObjects *pDynamicObject) ;
	void RemoveObjects(CDynamicObjects *pDynamicObject) ;

	void Update() ;

	void Gravity() ;

	void Collision(char coord) ;

	const std::vector<CDynamicObjects*> GetDynamicObjectsList() ;
	const CDynamicObjects* GetMainChar() ;
} ;

#define g_DynamicObjects_List CDynamicObjects_List::GetInstance()