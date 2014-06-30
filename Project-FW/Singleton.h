#pragma once

template <class T>
class Singleton
{
private :
	static T m_Instance ;

public :
	static T* GetInstance()
	{
		return &m_Instance ;
	}
} ;

template <class T> T Singleton<T>::m_Instance ;