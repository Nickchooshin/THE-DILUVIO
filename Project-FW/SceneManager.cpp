#include "SceneManager.h"
#include "Scene.h"

SceneManager::SceneManager() : m_pScene(0)
{
}
SceneManager::~SceneManager()
{
	m_pScene->Destroy() ;
	delete m_pScene ;
}

void SceneManager::StartScene(Scene *pScene)
{
	m_pScene = pScene ;
}

void SceneManager::InitScene()
{
	m_pScene->Init() ;
}

void SceneManager::UpdateScene(float dt)
{
	m_pScene->Update(dt) ;
}

void SceneManager::RenderScene()
{
	m_pScene->Render() ;
}

void SceneManager::DestroyScene()
{
	m_pScene->Destroy() ;
	delete m_pScene ;
}

void SceneManager::ChangeScene(Scene *pScene)
{
	DestroyScene() ;

	m_pScene = pScene ;

	InitScene() ;
}