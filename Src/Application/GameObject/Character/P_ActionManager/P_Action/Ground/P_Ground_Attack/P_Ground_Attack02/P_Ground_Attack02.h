#pragma once
#include"../../../P_ActionBase.h"

class Player;

class P_Ground_Attack02:public P_ActionBase
{
public:
	P_Ground_Attack02(std::weak_ptr<Player> a_owner, std::shared_ptr<ActionManager> a_manager) :P_ActionBase(a_owner, a_manager) {}
	~P_Ground_Attack02() {}

	void Init()override;
	void Update()override;

	void ActionStart()override;
	void ActionReset()override;

private:

	//移動速度
	float m_moveSpeed = 5.0f;


	//有効時間
	double m_cnt = 0.0;
	const double TIME = 0.2;	//攻撃自体の時間
	const double END_TIME = 0.5;
};
