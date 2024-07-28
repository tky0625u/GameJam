#pragma once
class ActionManager;
class EntityBase;

class ActionBase
{
public:
	ActionBase(std::shared_ptr<ActionManager> a_manager) {m_manager = a_manager; }
	~ActionBase() {}

	//クラスごとにアクションを変える
	virtual void Init() {}
	virtual void Update() {}

	virtual void ActionStart() {}
	virtual void ActionReset() {}
	void ChangeAction(std::string_view a_actionType);

	
	void SetOldTime() { m_oldActionTime = timeGetTime(); }	//終了時刻を記録
	bool PossibleAction();	//アクションを開始できるかどうか

protected:

	//自分の所属しているアクション管理クラス
	std::weak_ptr<ActionManager> m_manager;

	//前回アクションの終了時刻
	double m_oldActionTime = 0.0;

	//行動のクールタイム(入れなければ０)
	double m_coolTime=0.0;

};
