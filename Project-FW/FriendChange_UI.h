#pragma once

class CSprite ;

class CFriendChange_UI
{
public :
	float m_fX, m_fY ;
	float m_fRX, m_fRY ;

	CSprite *m_pSIcon[5] ;

	enum State_Change { NONE=0, LEFT, RIGHT } ;
	State_Change m_StateC ;

	enum State_Fade { DISABLE=0, FADE_IN, ENABLE, FADE_OUT } ;
	State_Fade m_StateF ;

	float m_fNowDegree, m_fMaxDegree ;
	float m_fDegree[5], m_fScale[5] ;

	int m_nNowAlpha, m_nAlphaSign ;

	float m_fAnimationTime, m_fFadeTime ;

	int m_nIconIndex, m_nIconListIndex[5] ;
	bool m_bIconChange ;

public :
	CFriendChange_UI() ;
	~CFriendChange_UI() ;

	void Init() ;

	void SetPosition(float fX, float fY) ;

	int GetSelectedIndex() ;

	void Update() ;

	void Render_Front() ;
	void Render_Behind() ;
private :
	void SetFadeState(State_Fade State) ;

	void Animation() ;
	void Fade() ;
	void SetCirclePosition() ;
} ;