#pragma once

#include "Singleton.h"
#include <dinput.h>

class Mouse : public Singleton<Mouse>
{
private :
	LPDIRECTINPUTDEVICE8 m_pDIDMouse ;

	DIMOUSESTATE MouseBuffer ;
public :
	enum MouseButtonType{LBUTTON_DOWN, LBUTTON_UP, RBUTTON_DOWN, RBUTTON_UP} ;

public :
	Mouse() ;
	~Mouse() ;

	bool Init() ;

	bool Update() ;

	bool IsMouse(MouseButtonType ButtonType) ;
} ;

#define g_Mouse Mouse::GetInstance()