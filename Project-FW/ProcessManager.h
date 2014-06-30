#pragma once

#include "Singleton.h"

class Process ;

class ProcessManager : public Singleton<ProcessManager>
{
private :
	Process *m_Process ;

public :
	ProcessManager() ;
	~ProcessManager() ;

	void StartProcess(Process *S_Process) ;
	void InitProcess() ;

	void UpdateProcess(float dt) ;
	void RenderProcess() ;

	void DestroyProcess() ;

	/* �߰� ���� */
	//void ChangeProcess() ;
	//void AddProcess() ;
} ;

#define g_ProcessManager ProcessManager::GetInstance()