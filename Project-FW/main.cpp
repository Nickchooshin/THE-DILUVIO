/*#include <d3d9.h>
#pragma warning( disable : 4996 ) // disable deprecated warning 
#include <strsafe.h>
#pragma warning( default : 4996 ) */

#include "WinSystem.h"
#include "SceneManager.h"
#include "SampleScene.h"

INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR, INT )
{
	CWinSystem WinSystem(hInst) ;

	g_SceneManager->StartScene(SampleScene::scene()) ;

	WinSystem.WinSet() ;	// WS_THICKFRAME - ������â �ø���/���̱� ũ������ ��������.
	WinSystem.WinMsg() ;
	WinSystem.WinEnd() ;

	return 0 ;
}