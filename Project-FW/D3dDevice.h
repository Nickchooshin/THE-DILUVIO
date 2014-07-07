#pragma once
#include "Singleton.h"
#include <d3dx9.h>

class D3dDevice : public Singleton<D3dDevice>
{
private :
	LPDIRECT3DDEVICE9 g_pd3dDevice ;
	int WinWidth, WinHeight ;
	float Time ;

public :
	D3dDevice() {}
	~D3dDevice() {}

	inline const LPDIRECT3DDEVICE9 GetDevice() { return g_pd3dDevice ; }
	inline const int GetWinWidth() { return WinWidth ; }
	inline const int GetWinHeight() { return WinHeight ; }
	inline const float GetTime() { return Time ; }

	friend class CD3dSystem ;
	friend class CWinSystem ;
} ;

#define g_D3dDevice D3dDevice::GetInstance()