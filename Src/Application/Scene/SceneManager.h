#pragma once

class BaseScene;

class SceneManager
{
public :

	// シーン情報
	enum class SceneType
	{
		Title,
		Game,
		Result,
	};

	void PreUpdate();
	void Update();
	void PostUpdate();

	void PreDraw();
	void Draw();
	void DrawSprite();
	void DrawDebug();

	// 次のシーンをセット (次のフレームから切り替わる)
	void SetNextScene(SceneType nextScene)
	{
		m_nextSceneType = nextScene;
	}

	// 現在のシーンのオブジェクトリストを取得
	const std::list<std::shared_ptr<KdGameObject>>& GetObjList();

	// 現在のシーンにオブジェクトを追加
	void AddObject(const std::shared_ptr<KdGameObject>& obj);
	void AddDefObject(const std::shared_ptr<KdGameObject>& a_obj, const std::string_view a_name, const Math::Vector3 a_pos);

	std::shared_ptr<BaseScene> GetScene() { return m_currentScene; }


	void RetentionTime(int _onetime, int _tentime, int _hundredtime, int _thousandtime);

	//スコアを他のシーンに
	const int GetOneTime() const { return m_onetime; }
	const int GetTenTime() const { return m_tentime; }
	const int GetHundredTime() const { return m_hundredtime; }
	const int GetThousandTime() const { return m_thousandtime; }

private :

	// マネージャーの初期化
	// インスタンス生成(アプリ起動)時にコンストラクタで自動実行
	void Init()
	{
		// 開始シーンに切り替え
		ChangeScene(m_currentSceneType);
	}

	// シーン切り替え関数
	void ChangeScene(SceneType sceneType);

	// 現在のシーンのインスタンスを保持しているポインタ
	std::shared_ptr<BaseScene> m_currentScene = nullptr;

	// 現在のシーンの種類を保持している変数
	SceneType m_currentSceneType = SceneType::Title;
	
	// 次のシーンの種類を保持している変数
	SceneType m_nextSceneType = m_currentSceneType;

	int m_onetime;				//1の位
	int m_tentime;				//10の位
	int m_hundredtime;			//100の位
	int m_thousandtime;			//1000の位

private:

	SceneManager() { Init(); }
	~SceneManager() {}

public:

	// シングルトンパターン
	// 常に存在する && 必ず1つしか存在しない(1つしか存在出来ない)
	// どこからでもアクセスが可能で便利だが
	// 何でもかんでもシングルトンという思考はNG
	static SceneManager& Instance()
	{
		static SceneManager instance;
		return instance;
	}
};
