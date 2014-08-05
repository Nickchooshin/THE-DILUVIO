#pragma once

#include "Objects.h"

class CObjects ;

class CEffect : public CObjects
{
protected :
	Circle m_BoundingCircle ;

	Size m_ImgSize, m_ColSize ;
	int m_nNowFrame ;
	int m_nEffectFrame ;
	Position m_Effect_Index ;

	float m_fAnimationTime ;

	enum State { EFFECT=0 } ;
	State m_State, m_prevState ;

public :
	CEffect() ;
	virtual ~CEffect() ;

	virtual void Init() = 0 ;

	const Circle GetBoundingCircle() ;
	
	virtual void Update() ;
	virtual void Effect(CObjects* pObject) ;
protected :
	void LoadDat(char *filepath) ;
	void SetBoundingBox() ;
	
	virtual void Animation() ;
} ;