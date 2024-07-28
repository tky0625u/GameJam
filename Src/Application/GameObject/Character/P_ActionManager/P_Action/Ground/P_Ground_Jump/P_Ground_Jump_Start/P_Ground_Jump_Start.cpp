#include"../../../../P_ActionManager.h"
#include "P_Ground_Jump_Start.h"

#include"Application/GameObject/Entitys/Character/Player/player.h"

void P_Ground_Jump_Start::Init()
{
}

void P_Ground_Jump_Start::Update()
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
	//カメラ方向に移動
	m_pPlayer.lock()->GetCamVec(_moveVec);

	//移動する
	_nowPos += _moveVec * (m_moveSpeed * DeltaTime::Instance().GetDeltaTime());
	m_pPlayer.lock()->SetPos(_nowPos);
	/////////////////////////////////////////////////////////////////////



	if (m_pPlayer.lock()->IsAnimEnd())
	{
		m_manager.lock()->ChangeAction("P_Air_Move");
	}

	//重力をかける////////////////////////////////////////////////////
	m_pPlayer.lock()->Grav();
	///////////////////////////////////////////////////////////////
}

void P_Ground_Jump_Start::ActionStart()
{
	m_pPlayer.lock()->SetAnimation("Jump_Start", false);
}

void P_Ground_Jump_Start::ActionReset()
{
}
