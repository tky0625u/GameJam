#include "SceneManager.h"

#include "BaseScene/BaseScene.h"
#include "TitleScene/TitleScene.h"
#include "GameScene/GameScene.h"
#include"ResultScene/ResultScene.h"

void SceneManager::PreUpdate()
{
	// シーン切替
	if (m_currentSceneType != m_nextSceneType)
	{
		ChangeScene(m_nextSceneType);
	}

	m_currentScene->PreUpdate();
}

void SceneManager::Update()
{
	m_currentScene->Update();
}

void SceneManager::PostUpdate()
{
	m_currentScene->PostUpdate();
}

void SceneManager::PreDraw()
{
	m_currentScene->PreDraw();
}

void SceneManager::Draw()
{
	m_currentScene->Draw();
}

void SceneManager::DrawSprite()
{
	m_currentScene->DrawSprite();
}

void SceneManager::DrawDebug()
{
	m_currentScene->DrawDebug();
}

const std::list<std::shared_ptr<KdGameObject>>& SceneManager::GetObjList()
{
	return m_currentScene->GetObjList();
}

void SceneManager::AddObject(const std::shared_ptr<KdGameObject>& obj)
{
	m_currentScene->AddObject(obj);
}

void SceneManager::AddDefObject(const std::shared_ptr<KdGameObject>& a_obj, const std::string_view a_name, const Math::Vector3 a_pos)
{
	//オブジェクトをリストに追加
	m_currentScene->AddObject(a_obj);
	a_obj->SetPos(a_pos);

	//デフォルトオブジェリストに追加
	m_currentScene->AddDefObject(a_obj, a_name, a_pos);
}

void SceneManager::RetentionTime(int _onetime, int _tentime, int _hundredtime, int _thousandtime)
{
	m_onetime = _onetime;
	m_tentime = _tentime;
	m_hundredtime = _hundredtime;
	m_thousandtime = _thousandtime;
}

void SceneManager::ChangeScene(SceneType sceneType)
{
	// 次のシーンを作成し、現在のシーンにする
	switch (sceneType)
	{
	case SceneType::Title:
		m_currentScene = std::make_shared<TitleScene>();
		break;
	case SceneType::Game:
		m_currentScene = std::make_shared<GameScene>();
		break;
	case SceneType::Result:
		m_currentScene = std::make_shared<ResultScene>();
	}
	m_currentScene->Init();

	// 現在のシーン情報を更新
	m_currentSceneType = sceneType;
}
