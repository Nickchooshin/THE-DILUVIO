#include "InputDevice.h"

InputDevice::InputDevice() : m_pDInput(NULL),
							 m_hWnd(NULL)
{
}
InputDevice::~InputDevice()
{
	if(m_pDInput!=NULL)
		m_pDInput->Release() ;
}

bool InputDevice::InitDevice(HINSTANCE hInstance, HWND hWnd)
{
	m_hWnd = hWnd ;

	// DirectInput�� ����� �� ���� ���� ��쿡, DirectInput�� �����.
	if(m_pDInput==NULL)
	{
		if( FAILED( DirectInput8Create( hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pDInput, NULL ) ) )
		{
			MessageBox(NULL, "DirectInput8Create Fail", "Error", MB_OK) ;
			return false ;
		}
	}

	return true ;
}