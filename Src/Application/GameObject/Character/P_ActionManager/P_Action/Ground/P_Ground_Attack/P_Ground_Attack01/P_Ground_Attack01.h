#pragma once
#include"../../../P_ActionBase.h"

class Character;

class P_Ground_Attack01:public P_ActionBase
{
public:
	P_Ground_Attack01(std::weak_ptr<Character> a_owner, std::shared_ptr<ActionManager> a_manager) :P_ActionBase(a_owner, a_manager) {}
	~P_Ground_Attack01() {}

	void Init()override;
	void Update()override;

	void ActionStart()override;
	void ActionReset()override;

private:

	//有効時間
	double m_cnt = 0.0;
	const double TIME = 75;	//攻撃自体の時間
	const double END_TIME = 75;

	bool m_actionEndFlg = false;
};
