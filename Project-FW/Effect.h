#pragma once

#include "Objects.h"

class CEffect : public CObjects
{
protected :
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
	
	virtual void Update() ;
protected :
	void LoadDat(char *filepath) ;
	void SetBoundingBox() ;
	
	virtual void Animation() ;
} ;