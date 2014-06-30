#pragma once

#include "Singleton.h"
#include <dinput.h>

class Keyboard : public Singleton<Keyboard>
{
private :
	LPDIRECTINPUTDEVICE8 m_pDIDKeyboard ;

	char KeyBuffer[256] ;

public :
	Keyboard() ;
	~Keyboard() ;

	bool Init() ;

	bool Update() ;

	bool IsButtonDown(BYTE Button) ;
	bool IsButtonUp(BYTE Button) ;
} ;

#define g_Keyboard Keyboard::GetInstance()