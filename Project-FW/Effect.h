#pragma once

#include "Objects.h"

class CObjects ;

class CEffect : public CObjects
{
protected :
	Circle m_BoundingCircle ;

	Size m_ImgSize, m_ColSize ;
	int m_nNowFrame ;
	int m_nNormalFrame, m_nEffect1Frame, m_nEffect2Frame ;
	Position m_Normal_Index, m_Effect1_Index, m_Effect2_Index ;

	float m_fAnimationTime ;

	enum State { NORMAL=0, EFFECT1, EFFECT2 } ;
	State m_State, m_prevState ;

	bool m_bVisible ;

public :
	CEffect() ;
	virtual ~CEffect() ;

	virtual void Init() = 0 ;

	const Circle GetBoundingCircle() ;

	const bool BeVisible() ;

	void SetVisible(bool bFlag) ;
	
	virtual void Update() ;
	virtual void Effect(CObjects* pObject) ;

	virtual void Render() ;
protected :
	void LoadDat(char *filepath) ;
	void SetBoundingBox() ;
	
	virtual void Animation() ;
} ;