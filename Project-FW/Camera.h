#pragma once
#include <d3dx9.h>

class CCamera
{
private :
	D3DXVECTOR3 m_Position ;
	float m_fWidth, m_fHeight ;

public :
	CCamera() ;
	~CCamera() ;

	void SetPosition(float x, float y) ;
	void MovePosition(float x, float y) ;

	void SetWolrdSize(float width, float height) ;

	void Run() ;
private :
	void CorrectionPosition() ;
} ;