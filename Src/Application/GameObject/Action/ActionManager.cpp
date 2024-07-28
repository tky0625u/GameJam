#include "ActionManager.h"
#include"ActionBase.h"

void ActionManager::Update()
{
	//クラスごとのイベント
	Event();

	if (m_currentAction.lock() == nullptr)return;
	m_currentAction.lock()->Update();
}

void ActionManager::ChangeAction(std::string_view a_actionType)
{
	//データタイプで探す
	auto _dataList = m_actionList.find(a_actionType.data());

	//なかったら終了
	if (_dataList == m_actionList.end())return;

	//アクションに移行できるか確認(なかったら終了)
	if (!_dataList->second->PossibleAction())return;


	//現在のアクションの終了
	if (m_currentAction.lock() != nullptr)
	{
		m_currentAction.lock()->ActionReset();
		m_currentAction.lock()->SetOldTime();
	}


	//アクションタイプに変更
	m_currentAction = _dataList->second;
	m_currentAction.lock()->ActionStart();

	//アクションの名前
	m_currentActionName = _dataList->first;
}
