#include "Keyboard.h"
#include "InputDevice.h"

Keyboard::Keyboard() : m_pDIDKeyboard(NULL)
{
	ZeroMemory(KeyBuffer, sizeof(KeyBuffer)) ;
	ZeroMemory(prevKeyBuffer, sizeof(prevKeyBuffer)) ;
}
Keyboard::~Keyboard()
{
	if(m_pDIDKeyboard!=NULL)
	{
		m_pDIDKeyboard->Unacquire() ;
		m_pDIDKeyboard->Release() ;
		m_pDIDKeyboard = NULL ;
	}
}

bool Keyboard::Init()
{
	// Ű���� DirectInputDevice �ʱ�ȭ
	if( FAILED( g_InputDevice->m_pDInput->CreateDevice( GUID_SysKeyboard, &m_pDIDKeyboard, NULL ) ) )
	{
		MessageBox(NULL, "Keyboard CreateDevice Fail", "Error", MB_OK) ;
		return false ;
	}

	// Ű���� DirectInputDevice ���� ����
	if( FAILED( m_pDIDKeyboard->SetDataFormat( &c_dfDIKeyboard ) ) )
	{
		MessageBox(NULL, "Keyboard SetDataFormat Fail", "Error", MB_OK) ;
		return false ;
	}

	// Ű���� DirectInputDevice �� �׼��� ������ ����
	// DISCL_EXCLUSIVE (�������) - �ٸ� ���ø����̼����� ��Ŀ�� �̵��� �ȵȴ�. ���콺�� Ű���带 �������� ����ϰ� �� ��� ������ �޴�, �̵�, ũ�� ������ �� �� ����. DISCL_BACKGROUND�� ���� ���� �� ����.
	// DISCL_FOREGROUND - ��Ŀ���� ������ ���� ���� ��� ����̽��� ������(����)�� ���� �� �Ѵ�.
	if( FAILED( m_pDIDKeyboard->SetCooperativeLevel( g_InputDevice->m_hWnd, DISCL_EXCLUSIVE | DISCL_FOREGROUND ) ) )
	{
		MessageBox(NULL, "KeyBoard SetCooperativeLevel Fail", "Error", MB_OK) ;
		return false ;
	}

	m_pDIDKeyboard->Acquire() ;										// Ű���� DirectInputDevice ����
	m_pDIDKeyboard->GetDeviceState(sizeof(KeyBuffer), &KeyBuffer) ;	// Ű���� DirectInputDevice ���� Ű������ ���¸� �����´�

	return true ;
}

HRESULT Keyboard::Update()
{
	HRESULT hr ;
	memcpy(prevKeyBuffer, KeyBuffer, sizeof(KeyBuffer)) ;
	ZeroMemory(KeyBuffer, sizeof(KeyBuffer)) ;

	// Ű���� ����̽��κ��� Ű������ ���¸� ������ �� ������
	// Ű������ ����̽��� �ٽ� �����Ѵ�
	if( FAILED( m_pDIDKeyboard->GetDeviceState( sizeof(KeyBuffer), &KeyBuffer ) ) )
	{
		hr = m_pDIDKeyboard->Acquire() ;

		while(hr == DIERR_INPUTLOST) // hr == DIERR_INPUTLOST || hr == E_ACCESSDENIED
		{
			hr = m_pDIDKeyboard->Acquire() ;
		}

		if( FAILED( hr ) )
			return hr ;
	}

	return S_OK ;
}

bool Keyboard::IsButtonDown(BYTE Button)
{
	if(KeyBuffer[Button] & 0x80)
		return true ;

	return false ;
}

bool Keyboard::IsButtonUp(BYTE Button)
{
	if(KeyBuffer[Button] & 0x80)
		return false ;

	return true ;
}

bool Keyboard::IsPressDown(BYTE Button)
{
	if((KeyBuffer[Button] & 0x80) && !(prevKeyBuffer[Button] & 0x80))
		return true ;

	return false ;
}
bool Keyboard::IsPressUp(BYTE Button)
{
	if(!(KeyBuffer[Button] & 0x80) && (prevKeyBuffer[Button] & 0x80))
		return true ;

	return false ;
}