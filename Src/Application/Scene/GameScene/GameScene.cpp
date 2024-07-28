#include "GameScene.h"
#include"../SceneManager.h"

#include"../../GameObject/BackGround/BackGround.h"
#include "../../GameObject/Terrain/Terrain.h"
#include "../../GameObject/Character/Character.h"

#include"../../GameObject/Character/Rod.h"

#include "../../GameObject/Camera/FPSCamera/FPSCamera.h"
#include "../../GameObject/Camera/TPSCamera/TPSCamera.h"
#include "../../GameObject/Camera/CCTVCamera/CCTVCamera.h"


#include"../../GameObject/UI/Life/Life.h"
#include"../../GameObject/UI/Distance/Distance.h"
#include"../../GameObject/Goal/Goal.h"

#include"../../GameObject/Terrain/Terrain.h"
#include"../../GameObject/BackGround/BackGround.h"

#include"../../GameObject/Enemy/Enemy5/Enemy5.h"
#include"../../GameObject/Enemy/Enemy6/Enemy6.h"

#include"../../GameObject/ObjectManager.h"

#include"../../GameObject/Start/Start.h"

#include"../../GameObject/Time/Time.h"

// 少数第n位で四捨五入する
void round_n(float& number, int n)
{
	number = number * pow(10, n - 1);
	number = round(number);
	number /= pow(10, n - 1);
}

void GameScene::Init()
{
	RegistObj();

	//オブジェクトの登録
	m_objManager = std::make_shared<ObjectManager>("Asset/Data/Game01.json");
	m_objManager->Init();

	//===================================================================
	//===================================================================
	// ステージ初期化
	std::shared_ptr<Terrain> _terrain = std::make_shared<Terrain>();
	_terrain->Init();
	AddObject(_terrain);

	std::shared_ptr<BackGround> _back = std::make_shared<BackGround>();
	_back->Init();
	AddObject(_back);
	//Load("CSV/Terrain/Terrain.csv");

	//===================================================================
	// キャラクター初期化
	//===================================================================
	std::shared_ptr<Character> _character = std::make_shared<Character>();
	_character->Init();
	AddObject(_character);

	std::shared_ptr<Rod> _rod = std::make_shared<Rod>();
	_rod->Init();
	AddObject(_rod);
	_rod->SetTarget(_character);



	std::shared_ptr<Start> _start = std::make_shared<Start>();
	_start->Init();
	AddObject(_start);
	_start->SetPlayer(_character);

	//時間
	std::shared_ptr<Time> _time;
	_time = std::make_shared<Time>();
	_time->Init();
	m_objList.push_back(_time);


	//std::shared_ptr<Enemy1> _enemy1 = std::make_shared<Enemy1>();
	//_enemy1->Init();
	//AddObject(_enemy1);

	//std::shared_ptr<Enemy2> _enemy2 = std::make_shared<Enemy2>();
	//_enemy2->Init();
	//AddObject(_enemy2);

	//std::shared_ptr<Enemy3> _enemy3 = std::make_shared<Enemy3>();
	//_enemy3->Init();
	//AddObject(_enemy3);

	//_enemy3->SetTarget(_character);

	//===================================================================
	// カメラ初期化
	//===================================================================
//	std::shared_ptr<FPSCamera>		_camera = std::make_shared<FPSCamera>();
	std::shared_ptr<TPSCamera>		_camera = std::make_shared<TPSCamera>();
//	std::shared_ptr<CCTVCamera>		_camera = std::make_shared<CCTVCamera>();
	_camera->Init();
	_camera->SetTarget(_character);
	//_camera->RegistHitObject(_terrain);
	_character->SetCamera(_camera);
	AddObject(_camera);

	m_cam = _camera;




	//残り距離
	std::shared_ptr<Distance> _distance;
	_distance = std::make_shared<Distance>();
	_distance->Init();
	m_objList.push_back(_distance);

	//ゴール(スイカ)
	std::shared_ptr<Goal> _goal;
	_goal = std::make_shared<Goal>();
	_goal->Init();
	m_objList.push_back(_goal);


	//距離クラスにプレイヤーをセット
	_distance->SetPlayer(_character);

	//距離クラスにゴールクラスをセット
	_distance->SetGoal(_goal);

	//ゴールクラスにプレイヤーをセット
	_goal->SetPlayer(_character);



	//==========================================================================================================
//ゴールクラスにタイムクラスをセット
//==========================================================================================================
	_goal->SetTime(_time);

	//==========================================================================================================
	//スタートクラスにタイムクラスをセット
	//==========================================================================================================
	_start->SetTime(_time);



	//音
	m_sewave = KdAudioManager::Instance().Play("Asset/Sounds/SE/sea.wav", true);
	if (m_sewave.expired() == false)
	{
		m_sewave.lock()->SetVolume(0.1f);
	}

	m_segaya = KdAudioManager::Instance().Play("Asset/Sounds/SE/gaya.wav", true);
	if (m_segaya.expired() == false)
	{
		m_segaya.lock()->SetVolume(0.3f);
	}

	//エフェクト初期化
	KdEffekseerManager::GetInstance().Create(1280, 720);

}

void GameScene::RegistObj()
{
	//敵１///////////////////////////////////////
	std::function<std::shared_ptr<Enemy6>()> fn1_ene = []()
	{
		//敵モデル
		std::shared_ptr<Enemy6>_enemy = std::make_shared<Enemy6>();
		_enemy->Init();
		_enemy->SetDir(Math::Vector3(1, 0, 0));

		return _enemy;
	};
	KdGameObjectFactory::Instance().RegisterCreateFunction("Enemy1", fn1_ene);
	////////////////////////////////////////////////////

	//敵2///////////////////////////////////////
	std::function<std::shared_ptr<Enemy6>()> fn2_ene = []()
	{
		//敵モデル
		std::shared_ptr<Enemy6>_enemy = std::make_shared<Enemy6>();
		_enemy->Init();

		return _enemy;
	};
	KdGameObjectFactory::Instance().RegisterCreateFunction("Enemy2", fn2_ene);
	////////////////////////////////////////////////////



	//建物////////////////////////////////////////////////////////////////
	//タワー１///////////////////////////////////////
	std::function<std::shared_ptr<Terrain>()> fn1_ter = []()
	{
		//地形モデル
		std::shared_ptr<KdModelData> m_spModel = std::make_shared<KdModelData>();
		m_spModel->Load("Asset/Models/Objet/Parasol/Parasol.gltf");

		std::shared_ptr<Terrain>_tower = std::make_shared<Terrain>();
		

		_tower->Init();
		_tower->SetType(m_spModel);

		return _tower;
	};
	KdGameObjectFactory::Instance().RegisterCreateFunction("Ter01", fn1_ter);
	////////////////////////////////////////////////////

	//タワー１///////////////////////////////////////
	std::function<std::shared_ptr<Terrain>()> fn1_ter2 = []()
	{
		//地形モデル
		std::shared_ptr<KdModelData> m_spModel = std::make_shared<KdModelData>();
		m_spModel->Load("Asset/Models/Objet/Beach_House/beach_house_COL.gltf");

		std::shared_ptr<Terrain>_tower = std::make_shared<Terrain>();
	

		_tower->Init();
		_tower->SetType(m_spModel);

		return _tower;
	};
	KdGameObjectFactory::Instance().RegisterCreateFunction("Ter02", fn1_ter2);
	////////////////////////////////////////////////////

	//タワー１///////////////////////////////////////
	std::function<std::shared_ptr<Terrain>()> fn1_ter3 = []()
	{
		//地形モデル
		std::shared_ptr<KdModelData> m_spModel = std::make_shared<KdModelData>();
		m_spModel->Load("Asset/Models/enemy1/enemy1.gltf");

		std::shared_ptr<Terrain>_tower = std::make_shared<Terrain>();


		_tower->Init();
		_tower->SetType(m_spModel);

		return _tower;
	};
	KdGameObjectFactory::Instance().RegisterCreateFunction("Ter03", fn1_ter3);
	////////////////////////////////////////////////////]


	//タワー１///////////////////////////////////////
	std::function<std::shared_ptr<Terrain>()> fn1_ter4 = []()
	{
		//地形モデル
		std::shared_ptr<KdModelData> m_spModel = std::make_shared<KdModelData>();
		m_spModel->Load("Asset/Models/Objet/Shark/Shark.gltf");

		std::shared_ptr<Terrain>_tower = std::make_shared<Terrain>();


		_tower->Init();
		_tower->SetType(m_spModel);

		return _tower;
	};
	KdGameObjectFactory::Instance().RegisterCreateFunction("Ter04", fn1_ter4);
	////////////////////////////////////////////////////


	//タワー１///////////////////////////////////////
	std::function<std::shared_ptr<Terrain>()> fn1_ter5 = []()
	{
		//地形モデル
		std::shared_ptr<KdModelData> m_spModel = std::make_shared<KdModelData>();
		m_spModel->Load("Asset/Models/Objet/Surfboards/surfboards.gltf");

		std::shared_ptr<Terrain>_tower = std::make_shared<Terrain>();


		_tower->Init();
		_tower->SetType(m_spModel);

		return _tower;
	};
	KdGameObjectFactory::Instance().RegisterCreateFunction("Ter05", fn1_ter5);
	////////////////////////////////////////////////////


}

void GameScene::Event()
{
	//gui用  行列計算//////////////////////////////////////////////////
	if (m_objManager != nullptr)
	{
		m_objManager->Update();
	}
	////////////////////////////////////////////////////////////////////
}


void GameScene::Load(std::string _filePath)
{
	//std::ifstream ifs(_filePath);

	//if (!ifs.is_open())return;

	//std::string lineString;

	//int z = 0;
	//int x = 0;

	//int ZMax = 0;
	//int XMax = 0;

	////砂
	//std::shared_ptr<KdModelData> sandModel = std::make_shared<KdModelData>();
	//sandModel->Load("Asset/Models/Terrain/Sand/Sand.gltf");
	////海
	//std::shared_ptr<KdModelData> seaModel = std::make_shared<KdModelData>();
	//seaModel->Load("Asset/Models/Terrain/Sea/Sea.gltf");

	//while (getline(ifs, lineString))
	//{
	//	std::istringstream iss(lineString);
	//	std::string commaData;

	//	while (getline(iss, commaData, ','))
	//	{
	//		std::shared_ptr<Terrain>   terrain = std::make_shared<Terrain>();
	//		switch (stoi(commaData))
	//		{
	//		case 0:
	//			terrain->SetModel(sandModel);
	//			break;
	//		case 1:
	//			terrain->SetModel(seaModel);
	//			break;
	//		}
	//		terrain->SetPos(Math::Vector3{ (x * 8.0f) - 100.0f,-5.0f,(z * 8.0f) - 50.0f });
	//		m_objList.push_back(terrain);
	//		z++;
	//	}
	//	ZMax = z;
	//	z = 0;
	//	x++;
	//	XMax = x;
	//}

	//std::shared_ptr<BackGround>  back = std::make_shared<BackGround>();
	//back->SetPos(Math::Vector3{ ((XMax * 8.0f) / 2.0f) - 100.0f,-5.0f,((ZMax * 8.0f) / 2.0f) - 50.0f });
	//back->Init();
	//m_objList.push_back(back);

	//ifs.close();
}