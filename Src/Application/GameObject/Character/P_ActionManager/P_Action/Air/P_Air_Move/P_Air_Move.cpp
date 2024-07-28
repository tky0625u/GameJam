#include"../../../P_ActionManager.h"
#include "P_Air_Move.h"

#include"Application/GameObject/Entitys/Character/Player/player.h"

void P_Air_Move::Init()
{
}

void P_Air_Move::Update()
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

	//重力をかける////////////////////////////////////////////////////
	m_pPlayer.lock()->Grav();
	///////////////////////////////////////////////////////////////

	//高速移動
	if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
	{
		m_manager.lock()->ChangeAction("P_Air_Dash");
	}

	//着地状態なら
	if (m_pPlayer.lock()->GetIsRand())
	{
		m_manager.lock()->ChangeAction("P_Ground_Jump_End");
	}

}

void P_Air_Move::ActionStart()
{
	//m_pPlayer.lock()->SetAnimation("Jump_Middle", false);
}

void P_Air_Move::ActionReset()
{
}
