#pragma once
#include <d3dx9.h>

class CCamera
{
private :
	D3DXVECTOR3 m_Position ;

public :
	CCamera() ;
	~CCamera() ;

	void SetPosition(float x, float y) ;
	void MovePosition(float x, float y) ;

	void Run() ;
} ;