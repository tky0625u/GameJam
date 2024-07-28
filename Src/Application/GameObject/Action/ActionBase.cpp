#include "ActionBase.h"
#include"ActionManager.h"

void ActionBase::ChangeAction(std::string_view a_actionType)
{
	//アクションを変更
	m_manager.lock()->ChangeAction(a_actionType);
}

//アクションが開始できるか
bool ActionBase::PossibleAction()
{
	//現在時刻を取得
	double _nowTime = timeGetTime();

	////クールタイムを過ぎていたら
	//if (DeltaTime::Instance().GetTimeDif(_nowTime,m_oldActionTime) > m_coolTime * DeltaTime::Instance().GetSlowInter())
	//{
	//	return true;
	//}
	//else
	//{
	//	return false;
	//}
	return true;
}
