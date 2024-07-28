#include"../../../../P_ActionManager.h"
#include "P_Ground_Move_End.h"

#include"Application/GameObject/Entitys/Character/Player/player.h"

void P_Ground_Move_End::Init()
{
}

void P_Ground_Move_End::Update()
{
	// キャラクターの移動
	//////////////////////////////////////////////////////////////////////
	Math::Vector3 _nowPos = m_pPlayer.lock()->GetPos();

	//一秒で最小速度
	if (m_moveSpeed > 0)
	{
		m_moveSpeed -= 100.0f * DeltaTime::Instance().GetDeltaTime();
		//0で止める
		if (m_moveSpeed <= 0)m_moveSpeed = 0;
	}

	//移動する
	_nowPos += m_moveVec * (m_moveSpeed * DeltaTime::Instance().GetDeltaTime());
	m_pPlayer.lock()->SetPos(_nowPos);
	/////////////////////////////////////////////////////////////////////



	if (m_pPlayer.lock()->IsAnimEnd())
	{
		m_manager.lock()->ChangeAction("P_Ground_Stand");
	}

	//重力をかける////////////////////////////////////////////////////
	m_pPlayer.lock()->Grav();
	///////////////////////////////////////////////////////////////
}

void P_Ground_Move_End::ActionStart()
{
	m_pPlayer.lock()->SetAnimation("Move_End", false);

	//移動速度初期化
	m_moveSpeed = 15.0f;

	m_moveVec = m_pPlayer.lock()->GetMatrix().Forward();
	m_moveVec.Normalize();
	////////////////////////////////////////////////////////////
}

void P_Ground_Move_End::ActionReset()
{
}
 