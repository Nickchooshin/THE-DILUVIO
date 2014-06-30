#include "ProcessManager.h"
#include "Process.h"

ProcessManager::ProcessManager() : m_Process(0)
{
}
ProcessManager::~ProcessManager()
{
	m_Process->Destroy() ;
}

void ProcessManager::StartProcess(Process *S_Process)
{
	m_Process = S_Process ;
}

void ProcessManager::InitProcess()
{
	m_Process->Init() ;
}

void ProcessManager::UpdateProcess(float dt)
{
	m_Process->Update(dt) ;
}

void ProcessManager::RenderProcess()
{
	m_Process->Render() ;
}

void ProcessManager::DestroyProcess()
{
	m_Process->Destroy() ;
}