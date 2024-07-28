#pragma once
#include"../../../P_ActionBase.h"

class Player;

class P_Ground_Jump_Start:public P_ActionBase
{
public:
	P_Ground_Jump_Start(std::weak_ptr<Player> a_owner, std::shared_ptr<ActionManager> a_manager) :P_ActionBase(a_owner, a_manager) {}
	~P_Ground_Jump_Start() {}

	void Init()override;
	void Update()override;

	void ActionStart()override;
	void ActionReset()override;

private:

	//移動速度
	Math::Vector3 m_moveVec = Math::Vector3::Zero;
	//移動速度
	float m_moveSpeed = 5.0f;

	//有効時間
	double m_cnt = 0.0;
	const double TIME = 0.3;

};
