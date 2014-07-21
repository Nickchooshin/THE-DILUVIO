#include "FriendChange_UI.h"
#include "Sprite.h"

#include "Keyboard.h"
#include "D3dDevice.h"


///
#include "Friends_List.h"

#include "Friends_Okulo.h"
#include "Friends_Montrilo.h"
//#include "Friends_Mano.h"
#include "Friends_Pilo.h"
#include "Friends_Makzelo.h"
#include "Friends_Vento.h"
#include "Friends_Busxo.h"
#include "Friends_Saltado.h"
#include "Friends_Elitro.h"
///

CFriendChange_UI::CFriendChange_UI() : m_fX(0.0f), m_fY(0.0f),
									   m_fRX(0.0f), m_fRY(0.0f),
									   m_StateC(NONE), m_StateF(DISABLE),
									   m_fNowDegree(0.0f), m_fMaxDegree(0.0f),
									   m_fAnimationTime(0.0f), m_fFadeTime(0.0f),
									   m_nNowAlpha(0), m_nAlphaSign(1),
									   m_nIconIndex(0),
									   m_bIconChange(false)
{
	for(int i=0; i<5; i++)
	{
		m_pSIcon[i] = NULL ;
		m_fDegree[i] = 0.0f ;
		m_fScale[i] = 1.0f ;
	}

	m_nIconListIndex[0] = 0 ;
	m_nIconListIndex[1] = 1 ;
	m_nIconListIndex[2] = 2 ;
	m_nIconListIndex[3] = -2 ;
	m_nIconListIndex[4] = -1 ;
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
		m_pSIcon[i]->Init(24.0f, 24.0f, "Resource/Image/Friends/Icon/SP_Symbol.png") ;
		m_pSIcon[i]->SetTextureUV((float)(i * 24), 24.0f, (float)((i+1) * 24), 48.0f) ;
	}

	///
	CFriends *pFriends ;
	g_Friends_List->SetMaxFriends(8) ;

	pFriends = new CFriends_Okulo ;
	pFriends->Init() ;
	g_Friends_List->AddFriend(pFriends) ;

	pFriends = new CFriends_Montrilo ;
	pFriends->Init() ;
	g_Friends_List->AddFriend(pFriends) ;

	pFriends = new CFriends_Pilo ;
	pFriends->Init() ;
	g_Friends_List->AddFriend(pFriends) ;

	pFriends = new CFriends_Makzelo ;
	pFriends->Init() ;
	g_Friends_List->AddFriend(pFriends) ;

	pFriends = new CFriends_Vento ;
	pFriends->Init() ;
	g_Friends_List->AddFriend(pFriends) ;

	pFriends = new CFriends_Busxo ;
	pFriends->Init() ;
	g_Friends_List->AddFriend(pFriends) ;

	pFriends = new CFriends_Saltado ;
	pFriends->Init() ;
	g_Friends_List->AddFriend(pFriends) ;

	pFriends = new CFriends_Elitro ;
	pFriends->Init() ;
	g_Friends_List->AddFriend(pFriends) ;
}

void CFriendChange_UI::SetPosition(float fX, float fY)
{
	m_fX = fX ;
	m_fY = fY ;
}

int CFriendChange_UI::GetSelectedIndex()
{
	return m_nIconListIndex[m_nIconIndex] ;
}

void CFriendChange_UI::Update()
{
	float fTime = g_D3dDevice->GetTime() ;
	float fSpeed = 0.0f ;

	if(m_StateC==NONE && g_Keyboard->IsButtonDown(DIK_A))
	{
		if(m_StateF==DISABLE)
			SetFadeState(FADE_IN) ;

		m_fFadeTime = 0.0f ;
		m_StateC = RIGHT ;
	}
	else if(m_StateC==NONE && g_Keyboard->IsButtonDown(DIK_S))
	{
		if(m_StateF==DISABLE)
			SetFadeState(FADE_IN) ;
		
		m_fFadeTime = 0.0f ;
		m_StateC = LEFT ;
	}

	for(int i=0; i<5; i++)
	{
		m_fDegree[i] += fSpeed * fTime ;
		if(m_fDegree[i]>=360.0f)
			m_fDegree[i] -= 360.0f ;
		else if(m_fDegree[i]<0.0f)
			m_fDegree[i] += 360.0f ;
	}

	Animation() ;
	Fade() ;

	SetCirclePosition() ;
}

void CFriendChange_UI::Render_Front()
{
	if(m_StateF==DISABLE)
		return ;

	for(int i=0; i<5; i++)
	{
		if(m_fScale[i]>=0.5f)
		{
			m_pSIcon[i]->SetAlpha(m_nNowAlpha) ;
			m_pSIcon[i]->Render() ;
		}
	}
}

void CFriendChange_UI::Render_Behind()
{
	if(m_StateF==DISABLE)
		return ;

	for(int i=0; i<5; i++)
	{
		if(m_fScale[i]<0.5f)
		{
			m_pSIcon[i]->SetAlpha(m_nNowAlpha) ;
			m_pSIcon[i]->Render() ;
		}
	}
}

void CFriendChange_UI::SetFadeState(State_Fade State)
{
	if(State==FADE_IN)
	{
		m_nNowAlpha = 102 ;
		m_nAlphaSign = 1 ;
		m_StateF = FADE_IN ;
	}
	else if(State==FADE_OUT)
	{
		m_nNowAlpha = 255 ;
		m_nAlphaSign = -1 ;
		m_StateF = FADE_OUT ;
		
		m_fFadeTime = 0.0f ;
	}
}

void CFriendChange_UI::Animation()
{
	if(m_StateC!=NONE)
	{
		m_fAnimationTime += g_D3dDevice->GetMoveTime() ;

		if(m_fNowDegree<=m_fMaxDegree && m_fAnimationTime>=0.2f)
		{
			float Degree = m_fAnimationTime / 0.2f ;
			m_fAnimationTime = 0.0f ;
			m_fNowDegree += Degree ;
			if(m_fNowDegree>m_fMaxDegree)
				Degree -= m_fNowDegree - m_fMaxDegree ;

			for(int i=0; i<5; i++)
			{
				if(m_StateC==LEFT)
					m_fDegree[i] -= Degree ;
				else if(m_StateC==RIGHT)
					m_fDegree[i] += Degree ;
			}

			if(m_fNowDegree>=m_fMaxDegree)
			{
				m_StateC = NONE ;
				m_fNowDegree = 0.0f ;
				m_bIconChange = false ;
			}
			else if(!m_bIconChange && m_fNowDegree>=m_fMaxDegree/2.0f)
			{
				m_bIconChange = true ;

				int nextIndex, prevIndex ;
				int size = g_Friends_List->GetSize() ;
				if(m_StateC==LEFT)
				{
					nextIndex = (m_nIconIndex + 3) % 5 ;
					prevIndex = (m_nIconIndex + 2) % 5 ;
					m_nIconListIndex[nextIndex] = m_nIconListIndex[prevIndex] + 1 ;
					if(m_nIconListIndex[nextIndex]>=size)
						m_nIconListIndex[nextIndex] -= size ;
					m_nIconIndex = (m_nIconIndex + 1) % 5 ;
				}
				else if(m_StateC==RIGHT)
				{
					nextIndex = (m_nIconIndex + 2) % 5 ;
					prevIndex = (m_nIconIndex + 3) % 5 ;
					m_nIconListIndex[nextIndex] = m_nIconListIndex[prevIndex] - 1 ;
					if(m_nIconListIndex[nextIndex]<0)
						m_nIconListIndex[nextIndex] += size ;
					m_nIconIndex = (m_nIconIndex - 1) % 5 ;
					if(m_nIconIndex<0)
						m_nIconIndex += 5 ;
				}
			}

			m_fAnimationTime = 0.0f ;
		}
	}
	else
		m_fAnimationTime = 0.0f ;
}

void CFriendChange_UI::Fade()
{
	if(m_StateF!=DISABLE)
	{
		m_fFadeTime += g_D3dDevice->GetTime() ;

		if(m_StateF==FADE_IN || m_StateF==FADE_OUT)
		{
			if(m_fFadeTime>=0.1f)
			{
				float Alpha = m_fFadeTime / 0.1f ;
				m_fFadeTime = 0.0f ;
				m_nNowAlpha += (int)(Alpha * 51.0f) * m_nAlphaSign ;

				if(m_StateF==FADE_IN && m_nNowAlpha>=255)
				{
					m_nNowAlpha = 255 ;
					m_StateF = ENABLE ;
				}
				else if(m_StateF==FADE_OUT && m_nNowAlpha<=102)
				{
					m_nNowAlpha = 0 ;
					m_StateF = DISABLE ;
				}
			}
		}
		else if(m_StateF==ENABLE)
		{
			if(m_fFadeTime>=3.0f)
				SetFadeState(FADE_OUT) ;
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

		Position index ;
		index = g_Friends_List->GetFriend(m_nIconListIndex[i])->GetIconIndex() ;
		m_pSIcon[i]->SetTextureUV((float)(index.x * 24), (float)(index.y * 24),
								  (float)((index.x+1) * 24), (float)((index.y+1) * 24)) ;

		m_pSIcon[i]->SetScale(m_fScale[i], m_fScale[i]) ;
		m_pSIcon[i]->SetPosition(x, y) ;
	}
}