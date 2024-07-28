#pragma once

class ActionBase;

class ActionManager : public std::enable_shared_from_this<ActionManager>
{
public:
	ActionManager() {}
	virtual ~ActionManager() {}

	virtual void Init() {}
	virtual void Event() {}

	void Update();

	//アクションを変える
	void ChangeAction(std::string_view a_actionType);

	//アクションの登録
	void RegisterAction(std::string_view a_dataType, std::shared_ptr<ActionBase> a_action)
	{

		//データタイプで探す
		auto _actionList = m_actionList.find(a_dataType.data());

		//なかったらデータタイプを登録
		if (_actionList == m_actionList.end())
		{
			m_actionList[a_dataType.data()] = a_action;
		}
	}

protected:


	//現在のアクション
	std::string_view m_currentActionName;
	std::weak_ptr<ActionBase> m_currentAction;

	//このクラスで行う行動
	std::unordered_map<std::string, std::shared_ptr<ActionBase>> m_actionList;


};
