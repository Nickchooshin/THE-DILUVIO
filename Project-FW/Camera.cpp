#include "Camera.h"
#include "D3dDevice.h"

CCamera::CCamera() : m_Position((float)(g_D3dDevice->GetWinWidth()/2),
								(float)(g_D3dDevice->GetWinHeight()/2),
								0.0f),
					 m_fWidth(0.0f), m_fHeight(0.0f)
{
}
CCamera::~CCamera()
{
}

void CCamera::SetPosition(float x, float y)
{
	m_Position.x = (float)((int) (x + 0.5f)) ;
	m_Position.y = (float)((int) (y + 0.5f)) ;
}

void CCamera::MovePosition(float x, float y)
{
	m_Position.x += (float)((int) (x + 0.5f)) ;
	m_Position.y += (float)((int) (y + 0.5f)) ;
}

void CCamera::SetWolrdSize(float width, float height)
{
	m_fWidth = width ;
	m_fHeight = height ;
}

void CCamera::Run()
{
	CorrectionPosition() ;

	const LPDIRECT3DDEVICE9 pd3dDevice = g_D3dDevice->GetDevice() ;
	const float WinWidth = (float)g_D3dDevice->GetWinWidth() ;
	const float WinHeight = (float)g_D3dDevice->GetWinHeight() ;

	D3DXMATRIXA16 matWorld ;
	D3DXMatrixIdentity( &matWorld ) ;
	pd3dDevice->SetTransform( D3DTS_WORLD, &matWorld ) ;

	D3DXVECTOR3 vEyePt( m_Position.x, m_Position.y, 0.0f ) ;	// 카메라의 위치
	D3DXVECTOR3 vLookatPt( m_Position.x, m_Position.y, 1.0f ) ;	// 카메라의 시선
	D3DXVECTOR3 vUpVec( 0.0f, 1.0f, 0.0f ) ;					// 상방벡터 (정수리)
	D3DXMATRIXA16 matView ;
	D3DXMatrixLookAtLH( &matView, &vEyePt, &vLookatPt, &vUpVec ) ;
	pd3dDevice->SetTransform( D3DTS_VIEW, &matView ) ;

	D3DXMATRIXA16 matProj;
	D3DXMatrixOrthoLH(&matProj, WinWidth, WinHeight, 0.0f, 1.0f) ;	// 카메라의 위치로부터 zn~zf 까지의 클리핑 영역이 지정되는 듯 함
	//D3DXMatrixOrthoOffCenterLH(&matProj, 0.0f, WinWidth, 0.0f, WinHeight, 0.0f, 1.0f) ;
	pd3dDevice->SetTransform( D3DTS_PROJECTION, &matProj ) ;
}

void CCamera::CorrectionPosition()
{
	if(m_fWidth==0.0f && m_fHeight==0.0f)
		return ;

	float fWinWidthHalf = g_D3dDevice->GetWinWidth() / 2.0f ;
	float fWinHeightHalf = g_D3dDevice->GetWinHeight() / 2.0f ;

	float PosX_Min, PosX_Max ;
	float PosY_Min, PosY_Max ;

	PosX_Min = fWinWidthHalf ;
	PosX_Max = m_fWidth - fWinWidthHalf ;
	PosY_Min = fWinHeightHalf ;
	PosY_Max = m_fHeight - fWinHeightHalf ;

	if(m_Position.x < PosX_Min)
		m_Position.x = PosX_Min ;
	else if(m_Position.x > PosX_Max)
		m_Position.x = PosX_Max ;

	if(m_Position.y < PosY_Min)
		m_Position.y = PosY_Min ;
	else if(m_Position.y > PosY_Max)
		m_Position.y = PosY_Max ;
}