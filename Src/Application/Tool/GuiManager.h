#pragma once
class BaseGui;

class GuiManager
{
public:


	void Init();
	void Update();

	//リストに追加
	void AddGuiList(const std::string_view a_name,std::shared_ptr<BaseGui> a_gui)
	{
		//データタイプで探す
		auto _guiList = m_guiList.find(a_name);

		//なかったらデータタイプを登録
		if (_guiList == m_guiList.end())
		{
			std::shared_ptr<BaseGui> _newData;
			m_guiList[a_name] = _newData;

			_guiList = m_guiList.find(a_name);
		}

		_guiList->second=a_gui;
	}

	//リストを検索
	std::shared_ptr<BaseGui> GetGui(std::string_view a_data)
	{
		//データタイプで探す
		auto _guiList = m_guiList.find(a_data);

		//なかったら終了
		if (_guiList == m_guiList.end())
		{
			return nullptr;
		}

		return _guiList->second;
	}


	//guiの数
	int GetGuiListSize() { return m_guiList.size(); }


private:

	//guiクラスのリスト
	std::unordered_map<std::string_view,std::shared_ptr<BaseGui>> m_guiList;


//=====================================================
// シングルトンパターン
//=====================================================
private:
	GuiManager() {}
	~GuiManager() {}


public:
	static GuiManager& Instance() {
		static GuiManager Instance;
		return Instance;
	}

};
