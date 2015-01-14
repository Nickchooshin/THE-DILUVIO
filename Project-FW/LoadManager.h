#pragma once

#include "Singleton.h"
#include <stdio.h>

class LoadManager : public Singleton<LoadManager>
{
private :
	FILE *m_File ;

public :
	LoadManager() ;
	~LoadManager() ;

	const bool OpenDat(char *filepath) ;
	const bool CloseDat() ;
	
	const bool GetItem(char *item) ;
	const bool GetString(char *str) ;
	const bool GetValue(int &value) ;
	const bool GetValue(float &value) ;
} ;

#define g_LoadManager LoadManager::GetInstance()