#include "D3dSystem.h"
#include "D3dDevice.h"
#include "InputDevice.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Joystick.h"
#include "TextureManager.h"
#include "Sprite.h"
#include "UISprite.h"
#include "Camera.h"
#include "MusicManager.h"

CD3dSystem::CD3dSystem() : m_pD3d(NULL),
						   m_pd3dDevice(NULL)
{
}
CD3dSystem::~CD3dSystem()
{
	if( m_pd3dDevice != NULL )
		m_pd3dDevice->Release();

	if( m_pD3d != NULL )
		m_pD3d->Release();
}

HRESULT CD3dSystem::InitD3d(const HINSTANCE hInst, const HWND hWnd, const int nWidth, const int nHeight, char* ErrorStr)
{
	if( NULL == ( m_pD3d = Direct3DCreate9( D3D_SDK_VERSION ) ) )
	{
		strcpy(ErrorStr, "DirectX�� �ʱ�ȭ ���� ���߽��ϴ�.") ;
		return E_FAIL;
	}

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory( &d3dpp, sizeof(d3dpp) );
	d3dpp.BackBufferWidth = nWidth ;			// ����� ����
	d3dpp.BackBufferHeight = nHeight ;			// ����� ����
	d3dpp.Windowed = TRUE ;						// â��� ����
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD ;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8 ;	// ����� ����	// D3DFMT_UNKNOWN
	d3dpp.BackBufferCount = 1 ;					// ����� ����
	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE ;	// ��Ƽ���ø� ��� ����
	d3dpp.MultiSampleQuality = 0 ;				// ��Ƽ���ø�(1x 2x 4x 8x ...)
	d3dpp.EnableAutoDepthStencil = true ;		// Direct3D�� ���̹��۸� ����� �����Ѵ�
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16 ;	// ���̹����� ũ�� ����(16bit ������ ����� ���̸� �Ǵ� ����)
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE ; // ����� �ֻ����� ���� ���� ����ȭ ����
	//

	if( FAILED( m_pD3d->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_MIXED_VERTEXPROCESSING, &d3dpp, &m_pd3dDevice ) ) )
	{
		printf("D3DCREATE_MIXED_VERTEXPROCESSING FAIL\n") ;
		//if( FAILED( m_pD3d->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &m_pd3dDevice ) ) )
		{
			if( FAILED( m_pD3d->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &m_pd3dDevice ) ) )
			{
				strcpy(ErrorStr, "DirectX ����̽��� �������� ���߽��ϴ�.") ;
				return E_FAIL;
			}
		}
	}

	m_hInst = hInst ;

	strcpy(ErrorStr, "InputDevice �ʱ�ȭ ����") ;

	if( !g_InputDevice->InitDevice(hInst, hWnd) )
		return E_FAIL ;
	if( !g_Keyboard->Init() )
		return E_FAIL ;
	if( !g_Mouse->Init() )
		return E_FAIL ;
	g_Joystick->Init() ;
	//if( !g_Joystick->Init() )
	//	return E_FAIL ;

	g_MusicManager->Initialize() ;

	g_D3dDevice->g_pd3dDevice = m_pd3dDevice ;
	g_D3dDevice->WinWidth = nWidth ;
	g_D3dDevice->WinHeight = nHeight ;

	SetRenderState() ;

	return S_OK;
}

LPDIRECT3DDEVICE9 CD3dSystem::GetDevice()
{
	return m_pd3dDevice ;
}

bool CD3dSystem::BeginScene()
{
	m_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0 ); // D3DCOLOR_XRGB

	return SUCCEEDED( m_pd3dDevice->BeginScene() ) ;
}

void CD3dSystem::EndScene()
{
	m_pd3dDevice->EndScene() ;
}

void CD3dSystem::Present()
{
	m_pd3dDevice->Present( NULL, NULL, NULL, NULL ) ;
}

void CD3dSystem::SetRenderState()
{
	m_pd3dDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );
	m_pd3dDevice->SetRenderState( D3DRS_DITHERENABLE, FALSE ); // �� ȥ�չ�
	m_pd3dDevice->SetRenderState( D3DRS_LIGHTING, FALSE );	// ����
	m_pd3dDevice->SetRenderState( D3DRS_SPECULARENABLE, FALSE ); // ���� ����

	m_pd3dDevice->SetRenderState( D3DRS_ZENABLE, FALSE ) ;	// Z����
	m_pd3dDevice->SetRenderState( D3DRS_ZWRITEENABLE, FALSE ) ;	// Z���� 2D ����??

	m_pd3dDevice->SetRenderState( D3DRS_ANTIALIASEDLINEENABLE, FALSE ) ;	// ��Ƽ�ٸ���� ������
}