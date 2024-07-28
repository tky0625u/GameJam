#pragma once
#include"../../P_ActionBase.h"

class Player;

class P_Air_Move:public P_ActionBase
{
public:
	P_Air_Move(std::weak_ptr<Player> a_owner, std::shared_ptr<ActionManager> a_manager) :P_ActionBase(a_owner, a_manager) {}
	~P_Air_Move() {}

	void Init()override;
	void Update()override;

	void ActionStart()override;
	void ActionReset()override;

private:

	//移動速度
	float m_moveSpeed = 5.0f;

};
