#pragma once

#include "Objects.h"
class CTiles : public CObjects
{
protected :
	Size m_ImgSize, m_ColSize ;
	int m_nNowFrame ;
	int m_nTileFrame, m_nEffect1Frame, m_nEffect2Frame ;
	Position m_Tile_Index ;
	Position m_Effect1_Index, m_Effect2_Index ;
	CTiles *m_pLinkedTile ;

	bool m_bCollision ;

	float m_fAnimationTime ;

	enum State { NORMAL=0, EFFECT1, EFFECT2 } ;
	State m_State, m_prevState ;

	char m_CollisionDirection ;
public :
	enum { COLLISION_LEFT=1, COLLISION_RIGHT=2, COLLISION_UP=4, COLLISION_DOWN=8 } ;

public :
	CTiles() ;
	virtual ~CTiles() ;

	virtual void Init() = 0 ;
	
	virtual void Update() ;
	virtual void Effect1() ;
	virtual void Effect2() ;

	void SetLinkedTile(CTiles *pLinkedTile) ;
	void SetCollision(bool bFlag) ;
	const bool BeCollision() ;

	void CollisionDirection(int direction) ;
protected :
	void LoadDat(char *filepath) ;
	void SetBoundingBox() ;
	
	virtual void Animation() ;
} ;