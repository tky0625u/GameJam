#include "TitleScene.h"
#include "../SceneManager.h"
#include"../../GameObject/Title/Title.h"

#include "../../GameObject/Camera/TitleCamera/TitleCamera.h"

#include"../../GameObject/BackGround/BackGround.h"
#include "../../GameObject/Terrain/Terrain.h"

void TitleScene::Event()
{
	
}

void TitleScene::Init()
{
	std::shared_ptr<Title> _title;
	_title = std::make_shared<Title>();
	_title->Init();
	m_objList.push_back(_title);

	//===================================================================
	// カメラ初期化
	//===================================================================
//	std::shared_ptr<FPSCamera>		_camera = std::make_shared<FPSCamera>();
	std::shared_ptr<TitleCamera>		_camera = std::make_shared<TitleCamera>();
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

}
