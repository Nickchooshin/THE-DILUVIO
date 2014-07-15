#include "Joystick.h"
#include "InputDevice.h"

Joystick::Joystick() : m_pDIDJoystick(NULL),
					   m_bReady(false)
{
}
Joystick::~Joystick()
{
	if(m_pDIDJoystick!=NULL)
	{
		m_pDIDJoystick->Unacquire() ;
		m_pDIDJoystick->Release() ;
		m_pDIDJoystick = NULL ;
	}
}

bool Joystick::Init()
{
	// ���̽�ƽ DirectInputDevice �ʱ�ȭ
	if( FAILED( g_InputDevice->m_pDInput->CreateDevice( GUID_Joystick, &m_pDIDJoystick, NULL ) ) )
	{
		//MessageBox(NULL, "Joystick CreateDevice Fail", "Error", MB_OK) ;
		return false ;
	}

	// ���̽�ƽ DirectInputDevice ���� ����
	if( FAILED( m_pDIDJoystick->SetDataFormat( &c_dfDIJoystick2 ) ) )
	{
		//MessageBox(NULL, "Joystick SetDataFormat Fail", "Error", MB_OK) ;
		return false ;
	}

	// ���̽�ƽ DirectInputDevice �� �׼��� ������ ����
	// DISCL_EXCLUSIVE (�������) - �ٸ� ���ø����̼����� ��Ŀ�� �̵��� �ȵȴ�. ���콺�� Ű���带 �������� ����ϰ� �� ��� ������ �޴�, �̵�, ũ�� ������ �� �� ����. DISCL_BACKGROUND�� ���� ���� �� ����.
	// DISCL_FOREGROUND - ��Ŀ���� ������ ���� ���� ��� ����̽��� ������(����)�� ���� �� �Ѵ�.
	if( FAILED( m_pDIDJoystick->SetCooperativeLevel( g_InputDevice->m_hWnd, DISCL_EXCLUSIVE | DISCL_FOREGROUND ) ) )
	{
		//MessageBox(NULL, "Joystick SetCooperativeLevel Fail", "Error", MB_OK) ;
		return false ;
	}

	// ���̽�ƽ�� �ɷ¿� ���� ������ �����Ѵ�. ���̳� ��ư���� ��Ʈ�ѷ��� ��, force feedback�� ����, �� ���̽�ƽ�� �����̳� ���� �ɼǿ� ���� �� ���� ��
	// DIDEVCAPS ����ü��, �ɷ� ������ ���� ������ ���
	DIDEVCAPS diDevCaps ;
	diDevCaps.dwSize = sizeof(DIDEVCAPS) ;
	if( FAILED( m_pDIDJoystick->GetCapabilities(&diDevCaps) ) )
	{
		//MessageBox(NULL, "Joystick GetCapabilities Fail", "Error", MB_OK) ;
		return false ;
	}

	// �޼����� ������ �μ� EnumAxesCallback ��, ���ŵ� ��ü�� �ʿ信 ���� ó���ϴ� �ݹ� �Լ��� �ּ��̴�.
	if( FAILED( m_pDIDJoystick->EnumObjects(EnumAxesCallback, (void*)g_InputDevice->m_hWnd, DIDFT_AXIS) ) )
	{
		//MessageBox(NULL, "Joystick EnumObjects Fail", "Error", MB_OK) ;
		return false ;
	}

	m_pDIDJoystick->Poll() ;

	m_bReady = true ;

	return true ;
}

BOOL CALLBACK EnumAxesCallback(const DIDEVICEOBJECTINSTANCE* instance, VOID* context)
{
    DIPROPRANGE propRange; 
    propRange.diph.dwSize       = sizeof(DIPROPRANGE); 
    propRange.diph.dwHeaderSize = sizeof(DIPROPHEADER); 
    propRange.diph.dwHow        = DIPH_BYID; 
    propRange.diph.dwObj        = instance->dwType;
    propRange.lMin              = -1000; 
    propRange.lMax              = +1000; 
    
    // Set the range for the axis
    if (FAILED(g_Joystick->m_pDIDJoystick->SetProperty(DIPROP_RANGE, &propRange.diph))) {
        return DIENUM_STOP;
    }

    return DIENUM_CONTINUE;
}

HRESULT Joystick::Update()
{
	if(!m_bReady)
		return false ;

	HRESULT hr ;

	// ���̽�ƽ ����̽��κ��� ���̽�ƽ�� ���¸� ������ �� ������
	// ���̽�ƽ�� ����̽��� �ٽ� �����Ѵ�
	hr = m_pDIDJoystick->Poll() ;

	if( FAILED(hr) )
	{
		hr = m_pDIDJoystick->Acquire() ;
		
		while(hr == DIERR_INPUTLOST) // hr == DIERR_INPUTLOST || hr == E_ACCESSDENIED
		{
			hr = m_pDIDJoystick->Acquire() ;
		}

		if( FAILED( hr ) )
			return hr ;
	}

	if( FAILED( hr = m_pDIDJoystick->GetDeviceState(sizeof(DIJOYSTATE2), &JoystickBuffer) ) )
		return hr ;

	return S_OK ;
}

bool Joystick::IsButtonDown(BYTE Button)
{
	if(JoystickBuffer.rgbButtons[Button] & 0x80)
		return true ;

	return false ;
}

bool Joystick::IsButtonUp(BYTE Button)
{
	if(JoystickBuffer.rgbButtons[Button] & 0x80)
		return false ;

	return true ;
}

bool Joystick::IsAxisMin(LONG Min, char Axis)
{
	LONG axis ;

	switch(Axis)
	{
	case 'x' :
	case 'X' :
		axis = JoystickBuffer.lX ;
		break ;

	case 'y' :
	case 'Y' :
		axis = JoystickBuffer.lY ;
		break ;

	case 'z' :
	case 'Z' :
		axis = JoystickBuffer.lZ ;
		break ;

	case 'r' :
	case 'R' :
		axis = JoystickBuffer.lRz ;
		break ;

	default :
		return false ;
	}

	if(axis>=Min)
		return true ;

	return false ;
}

bool Joystick::IsAxisMax(LONG Max, char Axis)
{
	LONG axis ;

	switch(Axis)
	{
	case 'x' :
	case 'X' :
		axis = JoystickBuffer.lX ;
		break ;

	case 'y' :
	case 'Y' :
		axis = JoystickBuffer.lY ;
		break ;

	case 'z' :
	case 'Z' :
		axis = JoystickBuffer.lZ ;
		break ;

	case 'r' :
	case 'R' :
		axis = JoystickBuffer.lRz ;
		break ;

	default :
		return false ;
	}

	if(axis<=Max)
		return true ;

	return false ;
}

bool Joystick::IsPov(DWORD Pov)
{
	if(JoystickBuffer.rgdwPOV[0]==Pov)
		return true ;

	return false ;
}