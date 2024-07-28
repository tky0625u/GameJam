#pragma once

class ObjectManager
{
public:

	ObjectManager(std::string_view a_path) { m_path = a_path;}
	~ObjectManager() { DataSave(); }

	void Init();
	void Update();

	//オブジェクトデータ型
	struct ObjData
	{
		std::weak_ptr<KdGameObject> m_obj;

		std::string m_objectName;
		std::string m_name;


		Math::Vector3 m_pos = {};
		float m_scale=0;
		float m_rotate = 0;
	};

	//オブジェクトの初期位置を登録
	void AddList(const std::shared_ptr<KdGameObject>& a_obj, const std::string_view a_name, const Math::Vector3 a_pos);
	void AddList(const std::shared_ptr<KdGameObject>& a_obj, const std::string_view a_name, const Math::Vector3 a_pos,const float a_scale,const float a_rotate);

private:

	
	void Release();


	//現在のシーンのオブジェクトを管理
	//std::unordered_map<std::string_view, std::vector<std::shared_ptr<ObjData>>> m_objMap;
	std::unordered_map<std::string, std::vector<std::shared_ptr<ObjData>>> m_objMap;
	//オブジェクトの名前
	std::vector<std::shared_ptr<std::string_view>> m_objName;


	//jsonファイルのパス
	std::string_view m_path;

	//jsonファイルからデータを確認
	void DataLoad();

	//jsonファイルにデータを保存
	void DataSave();


};
