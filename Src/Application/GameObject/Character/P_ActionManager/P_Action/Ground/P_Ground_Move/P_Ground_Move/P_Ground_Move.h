#pragma once
#include"../../../P_ActionBase.h"

class Character;

class P_Ground_Move:public P_ActionBase
{
public:
	P_Ground_Move(std::weak_ptr<Character> a_owner, std::shared_ptr<ActionManager> a_manager) :P_ActionBase(a_owner, a_manager) {}
	~P_Ground_Move() {}

	void Init()override;
	void Update()override;

	void ActionStart()override;
	void ActionReset()override;

private:

	//移動速度
	float m_moveSpeed = 0.02f;

	//移動する方向
	Math::Vector3 m_moveVec = Math::Vector3::Zero;

	bool m_actionEndFlg = false;

	//音のインスタンスを保存
	std::weak_ptr<KdSoundInstance> m_move;		//カウントダウン

};
