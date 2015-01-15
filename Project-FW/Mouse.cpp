#include "Mouse.h"
#include "InputDevice.h"

#include "D3dDevice.h"

Mouse::Mouse() : m_pDIDMouse(NULL),
				 MousePoint()
{
}
Mouse::~Mouse()
{
	if(m_pDIDMouse!=NULL)
	{
		m_pDIDMouse->Unacquire() ;
		m_pDIDMouse->Release() ;
		m_pDIDMouse = NULL ;
	}
}

bool Mouse::Init()
{
	// ���콺 DirectInputDevice �ʱ�ȭ
	if( FAILED( g_InputDevice->m_pDInput->CreateDevice( GUID_SysMouse, &m_pDIDMouse, NULL ) ) )
	{
		MessageBox(NULL, "Mouse CreateDevice Fail", "Error", MB_OK) ;
		return false ;
	}

	// ���콺 DirectInputDevice ���� ����
	if( FAILED( m_pDIDMouse->SetDataFormat( &c_dfDIMouse ) ) )
	{
		MessageBox(NULL, "Mouse SetDataFormat Fail", "Error", MB_OK) ;
		return false ;
	}

	// ���콺 DirectInputDevice �� �׼��� ������ ����
	// DISCL_EXCLUSIVE (�������) - �ٸ� ���ø����̼����� ��Ŀ�� �̵��� �ȵȴ�. ���콺�� Ű���带 �������� ����ϰ� �� ��� ������ �޴�, �̵�, ũ�� ������ �� �� ����. DISCL_BACKGROUND�� ���� ���� �� ����.
	// DISCL_FOREGROUND - ��Ŀ���� ������ ���� ���� ��� ����̽��� ������(����)�� ���� �� �Ѵ�.
	if( FAILED( m_pDIDMouse->SetCooperativeLevel( g_InputDevice->m_hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND ) ) )
	{
		MessageBox(NULL, "Mouse SetCooperativeLevel Fail", "Error", MB_OK) ;
		return false ;
	}

	m_pDIDMouse->Acquire() ;										// ���콺 DirectInputDevice ����

	return true ;
}

HRESULT Mouse::Update()
{
	HRESULT hr ;
	prevMouseBuffer = MouseBuffer ;

	// ���콺 ����̽��κ��� ���콺 ���¸� ������ �� ������
	// ���콺 ����̽��� �ٽ� �����Ѵ�
	if( FAILED( m_pDIDMouse->GetDeviceState( sizeof(MouseBuffer), &MouseBuffer ) ) )
	{
		hr = m_pDIDMouse->Acquire() ;

		while(hr == DIERR_INPUTLOST) // hr == DIERR_INPUTLOST || hr == E_ACCESSDENIED
		{
			hr = m_pDIDMouse->Acquire() ;
		}

		if( FAILED( hr ) )
			return hr ;
	}

	return S_OK ;
}

bool Mouse::IsMouse(MouseButtonType ButtonType)
{
	if(ButtonType == LBUTTON_DOWN && MouseBuffer.rgbButtons[0] == 0x80)
	{
		return TRUE ;
	}
	else if(ButtonType == LBUTTON_UP && MouseBuffer.rgbButtons[0] != 0x80)
	{
		return TRUE ;
	}
	else if(ButtonType == RBUTTON_DOWN && MouseBuffer.rgbButtons[1] == 0x80)
	{
		return TRUE ;
	}
	else if(ButtonType == RBUTTON_UP && MouseBuffer.rgbButtons[1] != 0x80)
	{
		return TRUE ;
	}
	else
	{
		return FALSE ;
	}
}

bool Mouse::IsMousePress(MouseButtonType ButtonType)
{
	if(ButtonType == LBUTTON_DOWN && ( MouseBuffer.rgbButtons[0] == 0x80 && prevMouseBuffer.rgbButtons[0] != 0x80 ))
	{
		return TRUE ;
	}
	else if(ButtonType == LBUTTON_UP && ( MouseBuffer.rgbButtons[0] != 0x80 && prevMouseBuffer.rgbButtons[0] == 0x80 ))
	{
		return TRUE ;
	}
	else if(ButtonType == RBUTTON_DOWN && ( MouseBuffer.rgbButtons[1] == 0x80 && prevMouseBuffer.rgbButtons[1] != 0x80 ))
	{
		return TRUE ;
	}
	else if(ButtonType == RBUTTON_UP && ( MouseBuffer.rgbButtons[1] != 0x80 && prevMouseBuffer.rgbButtons[1] == 0x80 ))
	{
		return TRUE ;
	}
	else
	{
		return FALSE ;
	}
}

void Mouse::SetMousePoint(int x, int y)
{
	int Height = g_D3dDevice->GetWinHeight() ;

	MousePoint.x = x ;
	MousePoint.y = Height - y ;
}

const POINT Mouse::GetMousePoint() const
{
	return MousePoint ;
}