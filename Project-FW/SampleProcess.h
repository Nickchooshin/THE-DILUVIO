#pragma once

#include "Process.h"

class SampleProcess : public Process
{
public :
	static Process* process() ;

	SampleProcess() ;
	virtual ~SampleProcess() ;

	void Init() ;
	void Destroy() ;

	void Update(float dt) ;
	void Render() ;
} ;