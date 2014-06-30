#pragma once

#include <Windows.h>
#include "D3dSystem.h"

class CWinSystem
{
private :
	HINSTANCE m_hInst ;
	WNDCLASSEX m_wc ;
	HWND m_hWnd ;
	int m_WinWidth, m_WinHeight ;

	CD3dSystem D3dSystem ;

	float t ;
	DWORD dwOldTime ;

public :
	CWinSystem(HINSTANCE hInst) ;
	~CWinSystem() ;

	void WinSet(LPCTSTR TitleName="FW_V - 0.1A", DWORD WinStyle=WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX, int WinWidth=640, int WinHeight=480) ;	// WS_THICKFRAME - ������â �ø���/���̱� ũ������ ��������.
	void WinMsg(int Frame=60) ;
	void WinEnd() ;
private :
	void Update() ;
	void Render() ;

	void MsgLoop(int Frame) ;
	friend LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) ;
} ;