#pragma once

#include <fmod.hpp>

class CSprite ;

class CButton
{
private :
	float m_fX, m_fY ;
	float m_fWidth, m_fHeight ;
	int m_nIndex[4] ;
	int m_nState, m_nPrevState ;
	bool m_bActivate, m_bClick, m_bPuton, m_bPutonActivate ;
	bool m_bVisible ;
	CSprite *m_pSprite ;

	FMOD::Sound *m_pClickDown, *m_pClickUp, *m_pPuton ;

public :
	CButton() ;
	~CButton() ;

	void Init(char *texfile) ;
	void Init(float Width, float Height, char *texfile) ;

	void SetPosition(float fX, float fY) ;
	void SetIndex(int normalIndex, int putonIndex, int clickIndex, int disableIndex) ;
	void SetActivate(bool bActivate) ;
	void SetVisible(bool bVisible) ;
	void SetPutonActivate(bool bActivate) ;
	void SetClickDownSound(char *filepath) ;
	void SetClickUpSound(char *filepath) ;
	void SetPutonSound(char *filepath) ;

	void SetAlpha(int nAlpha) ;

	void ClickState(int x, int y, bool bClick, bool bPress) ;
	const bool BeClick() const ;
	const bool BePuton() const ;
	const bool BeActivate() const ;
	const bool BeVisible() const ;

	void Render() ;
private :
	bool CollisionCheck(int x, int y) ;
} ;