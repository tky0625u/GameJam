#include "ResultScene.h"
#include"../../GameObject/Result/Result.h"
#include"../SceneManager.h"

#include "../../GameObject/Camera/ResultCamera/ResultCamera.h"

#include"../../GameObject/BackGround/BackGround.h"
#include "../../GameObject/Terrain/Terrain.h"

void ResultScene::Event()
{
	
}

void ResultScene::Init()
{
	std::shared_ptr<Result> _result;
	_result = std::make_shared<Result>();
	_result->Init();
	m_objList.push_back(_result);

	//===================================================================
	// カメラ初期化
	//===================================================================
//	std::shared_ptr<FPSCamera>		_camera = std::make_shared<FPSCamera>();
	std::shared_ptr<ResultCamera>		_camera = std::make_shared<ResultCamera>();
	//	std::shared_ptr<CCTVCamera>		_camera = std::make_shared<CCTVCamera>();
	_camera->Init();
	AddObject(_camera);

	m_cam = _camera;


	// ステージ初期化
	std::shared_ptr<Terrain> _terrain = std::make_shared<Terrain>();
	_terrain->Init();
	AddObject(_terrain);

	std::shared_ptr<BackGround> _back = std::make_shared<BackGround>();
	_back->Init();
	AddObject(_back);


	//音
	m_sewave = KdAudioManager::Instance().Play("Asset/Sounds/SE/sea.wav", true);
	if (m_sewave.expired() == false)
	{
		m_sewave.lock()->SetVolume(0.1f);
	}
}
