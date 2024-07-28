#include "ObjectManager.h"

#include"Application/Scene/SceneManager.h"
#include"Application/main.h"

#include"../Tool/GuiManager.h"
#include"../Tool/ObjectGui/ObjectGui.h"

//jsonライブラリ
#include <../Library/tinygltf/json.hpp>
// nlohmann::jsonを使いやすくするためのエイリアス
using json = nlohmann::json;

void ObjectManager::Init()
{
	//gui作成
	std::shared_ptr<BaseGui> _gui = std::make_shared<ObjectGui>("GameObject");
	GuiManager::Instance().AddGuiList("GameObject",_gui);

	//jsonファイルからロード
	DataLoad();
}

void ObjectManager::Release()
{
	//jsonファイルにデータをセーブ
	DataSave();
}

void ObjectManager::Update()
{
	/*for (const auto& objData : m_objMap)
	{
		for (const auto& obj : objData.second)
		{
			Math::Matrix _trans = Math::Matrix::CreateTranslation(obj->m_pos);
			Math::Matrix _scale = Math::Matrix::CreateScale(obj->m_scale);
			Math::Matrix _rotate = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(obj->m_rotate));
			Math::Matrix _mat = _scale * _rotate * _trans;

			obj->m_obj.lock()->SetMatrix(_mat);
		}
	}*/
}

void ObjectManager::AddList(const std::shared_ptr<KdGameObject>& a_obj, const std::string_view a_name, const Math::Vector3 a_pos)
{

	//データタイプで探す
	auto _objMap = m_objMap.find(a_name.data());


	//なかったらデータタイプを登録
	if (_objMap == m_objMap.end())
	{
		std::vector<std::shared_ptr<ObjData>> _newData;
		m_objMap[a_name.data()] = _newData;

		_objMap = m_objMap.find(a_name.data());
	}

	//同じオブジェクトが被らないようにする
	std::string _numStr = std::to_string(_objMap->second.size());
	std::string _newName =a_name.data() + std::string("  ")+_numStr;


	//オブジェクトを登録
	std::shared_ptr<ObjData> _data=std::make_shared<ObjData>(a_obj,a_name.data(), _newName, a_pos, 1.0f, 1.0f);
	_objMap->second.push_back(_data);

	Math::Matrix _trans = Math::Matrix::CreateTranslation(_data->m_pos);
	Math::Matrix _scale = Math::Matrix::CreateScale(_data->m_scale);
	Math::Matrix _rotate = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(_data->m_rotate));
	Math::Matrix _mat = _scale * _rotate * _trans;

	_data->m_obj.lock()->SetMatrix(_mat);
	_data->m_obj.lock()->SetBasePos(a_pos);
	_data->m_obj.lock()->SetPos(a_pos);
	

	//guiに登録     ""なら動く
	GuiManager::Instance().GetGui("GameObject")->SetDragFloat(_data->m_name,"pos.x", &_data->m_pos.x, 0.5f);
	GuiManager::Instance().GetGui("GameObject")->SetDragFloat(_data->m_name, "pos.y", &_data->m_pos.y, 0.5f);
	GuiManager::Instance().GetGui("GameObject")->SetDragFloat(_data->m_name, "pos.z", &_data->m_pos.z, 0.5f);

	GuiManager::Instance().GetGui("GameObject")->SetDragFloat(_data->m_name, "scale", &_data->m_scale, 0.1f);
	GuiManager::Instance().GetGui("GameObject")->SetSliderFloat(_data->m_name, "rotate", &_data->m_rotate, 0.0f, 360.0f);
}

void ObjectManager::AddList(const std::shared_ptr<KdGameObject>& a_obj, const std::string_view a_name, const Math::Vector3 a_pos, const float a_scale, const float a_rotate)
{
	//データタイプで探す
	auto _objMap = m_objMap.find(a_name.data());

	//なかったらデータタイプを登録
	if (_objMap == m_objMap.end())
	{
		std::vector<std::shared_ptr<ObjData>> _newData;
		m_objMap[a_name.data()] = _newData;

		_objMap = m_objMap.find(a_name.data());
	}

	//同じオブジェクトが被らないようにする
	std::string _numStr = std::to_string(_objMap->second.size());
	std::string _newName = a_name.data() + std::string("  ") + _numStr;


	//オブジェクトを登録
	std::shared_ptr<ObjData> _data = std::make_shared<ObjData>(a_obj, a_name.data(), _newName, a_pos, a_scale,a_rotate);
	_objMap->second.push_back(_data);

	Math::Matrix _trans = Math::Matrix::CreateTranslation(_data->m_pos);
	Math::Matrix _scale = Math::Matrix::CreateScale(_data->m_scale);
	Math::Matrix _rotate = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(_data->m_rotate));
	Math::Matrix _mat = _scale * _rotate * _trans;

	_data->m_obj.lock()->SetMatrix(_mat);

	_data->m_obj.lock()->SetBasePos(a_pos);
	_data->m_obj.lock()->SetPos(a_pos);


	//guiに登録     ""なら動く
	GuiManager::Instance().GetGui("GameObject")->SetDragFloat(_data->m_name, "pos.x", &_data->m_pos.x, 0.5f);
	GuiManager::Instance().GetGui("GameObject")->SetDragFloat(_data->m_name, "pos.y", &_data->m_pos.y, 0.5f);
	GuiManager::Instance().GetGui("GameObject")->SetDragFloat(_data->m_name, "pos.z", &_data->m_pos.z, 0.5f);

	GuiManager::Instance().GetGui("GameObject")->SetDragFloat(_data->m_name, "scale", &_data->m_scale, 0.1f);
	GuiManager::Instance().GetGui("GameObject")->SetSliderFloat(_data->m_name, "rotate", &_data->m_rotate, 0.0f, 360.0f);
}

void ObjectManager::DataLoad()
{
	// JSONファイルを読み込む
	std::ifstream file(m_path.data());
	if (!file.is_open()) {
		return;
	}

	json _data;
	file >> _data;

	//JSONデータを格納していく
	for (const auto& objData :_data["GameObject"])
	{
		Math::Vector3 _pos;
		float _scale = 0;
		float _rotate = 0;

		std::string _objectName = objData["objectName"];
		std::string _name = objData["name"];

		_pos.x = objData["pos.x"];
		_pos.y = objData["pos.y"];
		_pos.z = objData["pos.z"];

		_scale = objData["scale"];
		_rotate = objData["rotate"];


		std::shared_ptr<KdGameObject> _obj = KdGameObjectFactory::Instance().CreateGameObject(_objectName);
		SceneManager::Instance().AddObject(_obj);
		_obj->SetPos(_pos);

		//オブジェクトリストに追加
		AddList(_obj,_objectName, _pos,_scale,_rotate);
	}




}

void ObjectManager::DataSave()
{
	json _objData;

	//リストごと
	for (const auto& obj : m_objMap)
	{

		//オブジェクトごと
		for (const auto& _data : obj.second)
		{
			json _objStat;
			_objStat["objectName"] = _data->m_objectName.data();
			_objStat["name"] = _data->m_name.data();


			_objStat["pos.x"] = _data->m_pos.x;
			_objStat["pos.y"] = _data->m_pos.y;
			_objStat["pos.z"] = _data->m_pos.z;

			_objStat["scale"] = _data->m_scale;
			_objStat["rotate"] = _data->m_rotate;


			//ゲームオブジェクトに追加
			_objData["GameObject"][_data->m_name.data()] = _objStat;
		}

		
		
	}

	// ファイルに書き込む
	std::ofstream file(m_path.data());
	if (!file.is_open()) {
		return;
	}

	// JSONデータをファイルに書き込む
	file << std::setw(4) << _objData << std::endl; // Pretty print with 4-space indent
	file.close();
}

