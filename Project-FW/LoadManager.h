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
	void GetString(char *str) ;
	void GetValue(int &value) ;
} ;

#define g_LoadManager LoadManager::GetInstance()