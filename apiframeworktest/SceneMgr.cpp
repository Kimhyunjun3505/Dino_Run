#include "pch.h"
#include "SceneMgr.h"
#include "Scene_InGame.h"
#include "StartScene.h"
#include "EndScene.h"
#include "EventMgr.h"
SceneMgr::SceneMgr()
	: m_pCurScene(nullptr)
	, m_arrScene{}
{
}

SceneMgr::~SceneMgr()
{
	// �� ���� ����
	for (UINT i = 0; i < (UINT)SCENE_TYPE::END; ++i)
	{
		if (nullptr != m_arrScene[i])
		{
			delete m_arrScene[i];
		}
	}
}

void SceneMgr::ChangeScene(SCENE_TYPE _eNext)
{
	m_pCurScene->Exit();
	m_pCurScene = m_arrScene[(UINT)_eNext];
	m_pCurScene->Enter();
}

void SceneMgr::Init()
{
	// Scene ����
	m_arrScene[(UINT)SCENE_TYPE::START] = new StartScene;
	m_arrScene[(UINT)SCENE_TYPE::START]->SetName(L"Start");
	m_arrScene[(UINT)SCENE_TYPE::INGAME] = new Scene_InGame;
	m_arrScene[(UINT)SCENE_TYPE::INGAME]->SetName(L"InGame");
	m_arrScene[(UINT)SCENE_TYPE::GAMEOVER] = new EndScene;
	m_arrScene[(UINT)SCENE_TYPE::GAMEOVER]->SetName(L"GameOver");

//	m_arrScene[(UINT)SCENE_TYPE::TOOL] = new Scene_Tool;
//	m_arrScene[(UINT)SCENE_TYPE::SCENE_02] = new Scene02;


	// ���� �� ����
	m_pCurScene = m_arrScene[(UINT)SCENE_TYPE::START];
	m_pCurScene->Enter();
}

void SceneMgr::Update()
{
	m_pCurScene->Update();
	m_pCurScene->FinalUpdate();
}

void SceneMgr::Render(HDC _dc)
{ 
	m_pCurScene->Render(_dc);
	TCHAR ws2 = TCHAR(GetCurScene()->GetScore());
	TextOut(_dc, 1000, 80, &ws2, ws2);
}
