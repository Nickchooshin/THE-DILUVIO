#include "FriendChange_UI.h"
#include "Sprite.h"

#include "Keyboard.h"
#include "D3dDevice.h"

CFriendChange_UI::CFriendChange_UI() : m_fX(0.0f), m_fY(0.0f),
									   m_fRX(0.0f), m_fRY(0.0f),
									   m_State(NONE),
									   m_fNowDegree(0.0f),
									   m_fMaxDegree(0.0f)
{
	for(int i=0; i<5; i++)
	{
		m_pSIcon[i] = NULL ;
		m_fDegree[i] = 0.0f ;
		m_fScale[i] = 1.0f ;
	}
}
CFriendChange_UI::~CFriendChange_UI()
{
	for(int i=0; i<5; i++)
	{
		if(m_pSIcon[i]!=NULL)
			delete m_pSIcon[i] ;
	}
}

void CFriendChange_UI::Init()
{
	m_fRX = 40.0f ;
	m_fRY = 18.0f ;

	m_fMaxDegree = 72.0f ;

	for(int i=0; i<5; i++)
	{
		m_fDegree[i] = (float)((360 / 5) * i - 90) ;
		m_fScale[i] = 1.0f ;

		m_pSIcon[i] = new CSprite ;
	}
	m_pSIcon[0]->Init("Resource/Image/Friend/Icon/SP_Symbol_Busxo.png") ;
	m_pSIcon[1]->Init("Resource/Image/Friend/Icon/SP_Symbol_Elitro.png") ;
	m_pSIcon[2]->Init("Resource/Image/Friend/Icon/SP_Symbol_Makzelo.png") ;
	m_pSIcon[3]->Init("Resource/Image/Friend/Icon/SP_Symbol_Man-o.png") ;
	m_pSIcon[4]->Init("Resource/Image/Friend/Icon/SP_Symbol_Montrilo.png") ;
}

void CFriendChange_UI::SetPosition(float fX, float fY)
{
	m_fX = fX ;
	m_fY = fY ;
}

void CFriendChange_UI::Update()
{
	float fTime = g_D3dDevice->GetTime() ;
	float fSpeed = 0.0f ;

	if(m_State==NONE && g_Keyboard->IsButtonDown(DIK_A))
	{
		fSpeed += -2.0f ;
	}
	if(m_State==NONE && g_Keyboard->IsButtonDown(DIK_S))
	{
		fSpeed += 2.0f ;
	}

	for(int i=0; i<5; i++)
	{
		m_fDegree[i] += fSpeed * fTime ;
		if(m_fDegree[i]>=360.0f)
			m_fDegree[i] -= 360.0f ;
		else if(m_fDegree[i]<0.0f)
			m_fDegree[i] += 360.0f ;
	}

	//Animation() ;

	SetCirclePosition() ;
}

void CFriendChange_UI::Render()
{
	for(int i=0; i<5; i++)
		m_pSIcon[i]->Render() ;
}

void CFriendChange_UI::Render_Front()
{
	for(int i=0; i<5; i++)
	{
		if(m_fScale[i]>=0.5f)
			m_pSIcon[i]->Render() ;
	}
}

void CFriendChange_UI::Render_Behind()
{
	for(int i=0; i<5; i++)
	{
		if(m_fScale[i]<0.5f)
			m_pSIcon[i]->Render() ;
	}
}

void CFriendChange_UI::Animation()
{
	static float fTime=0.0f ;
	fTime += g_D3dDevice->GetTime() ;

	if(m_fNowDegree<m_fMaxDegree && fTime>=0.2f)
	{
		float Degree = fTime / 0.2f ;
		fTime = 0.0f ;
		m_fNowDegree += Degree ;

		for(int i=0; i<5; i++)
		{
			if(m_State==LEFT)
				m_fDegree[i] -= Degree ;
			else
				m_fDegree[i] += Degree ;
		}
	}
}

void CFriendChange_UI::SetCirclePosition()
{
	float x, y ;

	for(int i=0; i<5; i++)
	{
		x = cos((m_fDegree[i] * D3DX_PI) / 180) ;
		y = sin((m_fDegree[i] * D3DX_PI) / 180) ;

		m_fScale[i] = 1.0f / (y+2.0f) ;

		x = (x * m_fRX) + m_fX ;
		y = (y * m_fRY) + m_fY ;

		m_pSIcon[i]->SetScale(m_fScale[i], m_fScale[i]) ;
		m_pSIcon[i]->SetPosition(x, y) ;
	}
}