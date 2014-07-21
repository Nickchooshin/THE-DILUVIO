#pragma once

class CSprite ;

class CFriendChange_UI
{
public :
	float m_fX, m_fY ;
	float m_fRX, m_fRY ;

	CSprite *m_pSIcon[5] ;

	enum State { NONE=0, LEFT, RIGHT } ;
	State m_State ;

	float m_fNowDegree ;
	float m_fMaxDegree ;
	float m_fDegree[5], m_fScale[5] ;

	float m_fAnimationTime ;

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
	void Animation() ;
	void SetCirclePosition() ;
} ;