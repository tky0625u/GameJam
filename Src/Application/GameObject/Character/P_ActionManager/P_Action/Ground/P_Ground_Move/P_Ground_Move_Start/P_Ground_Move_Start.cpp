#include"../../../../P_ActionManager.h"
#include "P_Ground_Move_Start.h"

#include"Application/GameObject/Entitys/Character/Player/player.h"

void P_Ground_Move_Start::Init()
{
}

void P_Ground_Move_Start::Update()
{
	// キャラクターの移動
	//////////////////////////////////////////////////////////////////////
	Math::Vector3 _nowPos = m_pPlayer.lock()->GetPos();

	Math::Vector3 _moveVec = Math::Vector3::Zero;
	if (GetAsyncKeyState('D')) { _moveVec.x += 1.0f; }
	if (GetAsyncKeyState('A')) { _moveVec.x += -1.0f; }
	if (GetAsyncKeyState('W')) { _moveVec.z += 1.0f; }
	if (GetAsyncKeyState('S')) { _moveVec.z += -1.0f; }

	_moveVec.Normalize();
	////カメラ方向に移動
	m_pPlayer.lock()->GetCamVec(_moveVec);


	//一秒で最大速度
	if (m_moveSpeed < 15.0f)
	{
		m_moveSpeed += 20.0f * DeltaTime::Instance().GetDeltaTime();
		//0で止める
		if (m_moveSpeed >= 15.0f)m_moveSpeed = 15.0f;
	}

	//移動する
	_nowPos += _moveVec * (m_moveSpeed * DeltaTime::Instance().GetDeltaTime());
	m_pPlayer.lock()->SetPos(_nowPos);

	/////////////////////////////////////////////////////////////////////



	if (m_pPlayer.lock()->IsAnimEnd())
	{
		m_manager.lock()->ChangeAction("P_Ground_Move");
	}

	//重力をかける////////////////////////////////////////////////////
	m_pPlayer.lock()->Grav();
	///////////////////////////////////////////////////////////////
}

void P_Ground_Move_Start::ActionStart()
{
	m_pPlayer.lock()->SetAnimation("Move_Start", false);

	//移動速度初期化
	m_moveSpeed = 0.0f;

}

void P_Ground_Move_Start::ActionReset()
{
}
