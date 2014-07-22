#pragma once

#include "Objects.h"
class CTiles : public CObjects
{
private :
	Size m_ImgSize, m_ColSize ;
	int m_nNowFrame ;
	int m_nTileFrame, m_nEffectFrame ;
	Position m_Tile_Index ;
	Position m_Effect_Index ;

	float m_fAnimationTime ;

	enum State { NORMAL=0, EFFECT } ;
	State m_State, m_prevState ;

public :
	CTiles() ;
	virtual ~CTiles() ;

	virtual void Init() = 0 ;
	
	virtual void Update() ;

protected :
	void LoadDat(char *filepath) ;
	void SetBoundingBox() ;
	
	virtual void Animation() ;
} ;