#pragma once

#include "Singleton.h"
#include <vector>

class CDynamicObjects ;

class CDynamicObjects_List : public Singleton<CDynamicObjects_List>
{
private :
	CDynamicObjects *m_MainChar ;
	std::vector<CDynamicObjects*> m_DynamicObjects_List ;

public :
	CDynamicObjects_List() ;
	~CDynamicObjects_List() ;

	void AddMainCharObjects(CDynamicObjects *pObjects) ;
	void AddObjects(CDynamicObjects *pObjects) ;
	void RemoveObjects(CDynamicObjects *pObjects) ;

	void Update() ;

	void Gravity() ;

	void Collision(char coord) ;
} ;

#define g_DynamicObjects_List CDynamicObjects_List::GetInstance()