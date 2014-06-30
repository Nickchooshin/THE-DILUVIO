#pragma once
#include "Singleton.h"
#include <d3dx9.h>

class D3dDevice : public Singleton<D3dDevice>
{
private :
	LPDIRECT3DDEVICE9 g_pd3dDevice ;
	int WinWidth, WinHeight ;

public :
	D3dDevice() {}
	~D3dDevice() {}

	inline const LPDIRECT3DDEVICE9 GetDevice() { return g_pd3dDevice ; }
	inline const int GetWinWidth() { return WinWidth ; }
	inline const int GetWinHeight() { return WinHeight ; }

	friend class CD3dSystem ;
} ;

#define g_D3dDevice D3dDevice::GetInstance()