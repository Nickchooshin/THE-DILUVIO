#pragma once

class Process
{
public :
	Process() {}
	virtual ~Process() {}

	virtual void Init() = 0 ;
	virtual void Destroy() = 0 ;

	virtual void Update(float dt) = 0 ;
	virtual void Render() = 0 ;
private :
	//virtual void InputUpdate() = 0 ;
} ;