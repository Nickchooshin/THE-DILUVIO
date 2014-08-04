#pragma once

typedef struct _Vector
{
	float x ;
	float y ;

	_Vector() : x(0.0f),
				y(0.0f)
	{}
	_Vector(float X, float Y) : x(X),
								y(Y)
	{}

	const _Vector operator+(_Vector vec)
	{
		_Vector temp ;
		temp.x = x + vec.x ;
		temp.y = y + vec.y ;

		return temp ;
	}
	const _Vector& operator=(_Vector vec)
	{
		x = vec.x ;
		y = vec.y ;

		return *this ;
	}
	const _Vector& operator+=(_Vector vec)
	{
		*this = *this + vec ;

		return *this ;
	}
} Vector ;

typedef struct _SIZE
{
	int x ;
	int y ;

	_SIZE() : x(0),
			  y(0)
	{}
	_SIZE(int X, int Y) : x(X),
						  y(Y)
	{}

	const _SIZE operator+(_SIZE size)
	{
		_SIZE temp ;
		temp.x = x + size.x ;
		temp.y = y + size.y ;

		return temp ;
	}
	const _SIZE& operator=(_SIZE size)
	{
		x = size.x ;
		y = size.y ;

		return *this ;
	}
	const _SIZE& operator+=(_SIZE size)
	{
		*this = *this + size ;

		return *this ;
	}
	//
	const bool operator<(_SIZE size) const
	{
		return (this->x + this->y) < (size.x + size.y) ;
	}
} Size, Position ;

typedef struct _Rect
{
	int left, top, right, bottom ;
} Rect ;

typedef struct _Circle
{
	Position pos ;
	float radius ;
} Circle ;

class CSprite ;

class CObjects
{
protected :
	CSprite *m_pSprite ;
	float m_fX, m_fY ;
	Rect m_BoundingBox ;

public :
	CObjects() ;
	virtual ~CObjects() ;

	virtual void Init() = 0 ;

	const float GetPositionX() ;
	const float GetPositionY() ;

	void SetPosition(float fX, float fY) ;

	const Rect GetBoundingBox() ;

	virtual void Render() ;
protected :
	virtual void SetBoundingBox() = 0 ;
} ;