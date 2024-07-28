#pragma once

class CameraBase;

class ObjectManager;

class BaseScene
{
public :

	BaseScene() {  }
	virtual ~BaseScene() {}

	virtual void Init();

	void PreUpdate();
	void Update();
	void PostUpdate();

	void PreDraw();
	void Draw();
	void DrawSprite();
	void DrawDebug();

	// オブジェクトリストを取得
	const std::list<std::shared_ptr<KdGameObject>>& GetObjList()
	{
		return m_objList;
	}
	
	// オブジェクトリストに追加
	void AddObject(const std::shared_ptr<KdGameObject>& obj)
	{
		m_objList.push_back(obj);
	}

	//デフォルトのオブジェクト追加
	void AddDefObject(const std::shared_ptr<KdGameObject>& a_obj, const std::string_view a_name, const Math::Vector3 a_pos);

	//カメラを取得
	std::weak_ptr<CameraBase> GetCamera() { return m_cam; }

protected :

	// 継承先シーンで必要ならオーバーライドする
	virtual void Event();


	// 全オブジェクトのアドレスをリストで管理
	std::list<std::shared_ptr<KdGameObject>> m_objList;

	//カメラを保存
	std::weak_ptr<CameraBase> m_cam;

	std::shared_ptr<ObjectManager> m_objManager = nullptr;
};
