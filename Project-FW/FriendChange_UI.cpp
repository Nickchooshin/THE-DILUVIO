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
									   m_State(NONE),
									   m_fNowDegree(0.0f),
									   m_fMaxDegree(0.0f),
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

	if(m_State==NONE && g_Keyboard->IsButtonDown(DIK_A))
	{
		m_State = RIGHT ;
	}
	else if(m_State==NONE && g_Keyboard->IsButtonDown(DIK_S))
	{
		m_State = LEFT ;
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

	SetCirclePosition() ;
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

	if(m_State!=NONE)
	{
		//fTime += g_D3dDevice->GetTime() ;
		fTime += g_D3dDevice->GetMoveTime() ;

		if(m_fNowDegree<=m_fMaxDegree && fTime>=0.2f)
		{
			float Degree = fTime / 0.2f ;
			fTime = 0.0f ;
			m_fNowDegree += Degree ;
			if(m_fNowDegree>m_fMaxDegree)
				Degree -= m_fNowDegree - m_fMaxDegree ;

			for(int i=0; i<5; i++)
			{
				if(m_State==LEFT)
					m_fDegree[i] -= Degree ;
				else if(m_State==RIGHT)
					m_fDegree[i] += Degree ;
			}

			if(m_fNowDegree>=m_fMaxDegree)
			{
				m_State = NONE ;
				m_fNowDegree = 0.0f ;
				m_bIconChange = false ;
			}
			else if(!m_bIconChange && m_fNowDegree>=m_fMaxDegree/2.0f)
			{
				m_bIconChange = true ;

				int nextIndex, prevIndex ;
				int size = g_Friends_List->GetSize() ;
				if(m_State==LEFT)
				{
					nextIndex = (m_nIconIndex + 3) % 5 ;
					prevIndex = (m_nIconIndex + 2) % 5 ;
					m_nIconListIndex[nextIndex] = m_nIconListIndex[prevIndex] + 1 ;
					if(m_nIconListIndex[nextIndex]>=size)
						m_nIconListIndex[nextIndex] -= size ;
					m_nIconIndex = (m_nIconIndex + 1) % 5 ;
				}
				else if(m_State==RIGHT)
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

			fTime = 0.0f ;
		}
	}
	else
		fTime = 0.0f ;

	//fTime = 0.0f ;
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