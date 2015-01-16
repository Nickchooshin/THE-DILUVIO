#pragma once
#include <d3dx9.h>

class CSprite
{
protected :
	LPDIRECT3DVERTEXBUFFER9	m_pVB ;
	LPDIRECT3DINDEXBUFFER9	m_pIB ;
	LPDIRECT3DTEXTURE9		m_pTexture ;
	D3DXIMAGE_INFO			*m_pTexInfo ;

	float m_fWidth, m_fHeight ;
	D3DXVECTOR3 m_Position ;
	D3DXVECTOR3 m_CenterPosition ;
	float m_fScaleX, m_fScaleY ;
	float m_fAngle[3] ;
	int m_R, m_G, m_B ;
	int m_nAlpha ;
	float m_tu[4], m_tv[4] ;

public :
	CSprite() ;
	virtual ~CSprite() ;

	bool Init(char *texfile) ;
	bool Init(float Width, float Height, char *texfile) ;

	void SetPosition(float X, float Y) ;						// ��ǥ���� (�߾� ����)
	void SetPositionX(float X) ;
	void SetPositionY(float Y) ;
	void SetPositionZ(float Z) ;								// Z�� ��ǥ����
	void SetCenterPosition(float CenterX, float CenterY) ;		// �߽��� ����
	void SetScale(float ScaleX, float ScaleY) ;					// Ȯ��, ���
	void SetAngle(float Angle, char Direction='z') ;			// ���� ���� (�ݽð����)
	void SetRGB(int R, int G, int B) ;							// RGB�� ����
	void SetAlpha(int Alpha) ;									// ���İ� ���� 0~255
	
	bool SetTexture(char *texfile) ;
	void SetTextureUV(float u1, float v1, float u2, float v2) ;	// �ؽ��� UV ����
	void TexReverse() ;											// �ؽ��� ������

	D3DXVECTOR3 GetPosition() ;									// ��ǥ �޾ƿ���

	void Render() ;
private :
	HRESULT InitVB() ;

	//bool SetTexture(char *texfile) ;
	void SetupMatrices() ;
} ;

struct SPRITE_VERTEX
{
	float		x, y, z ;	// The position
	D3DCOLOR	color ;		// The color
	float		tu, tv ;	// The texture coordinates (x, y)
} ;

#define D3DFVF_SPRITE_VERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)