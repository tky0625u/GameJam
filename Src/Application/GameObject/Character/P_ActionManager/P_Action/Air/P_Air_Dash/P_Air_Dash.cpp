#include"../../../P_ActionManager.h"
#include "P_Air_Dash.h"

#include"Application/GameObject/Entitys/Character/Player/player.h"

void P_Air_Dash::Init()
{
	//クールタイムの設定
	m_coolTime = 1.0;
}

void P_Air_Dash::Update()
{
	// キャラクターの移動
	//////////////////////////////////////////////////////////////////////
	Math::Vector3 _nowPos = m_pPlayer.lock()->GetPos();


	//移動する
	_nowPos += m_moveVec * (m_moveSpeed * DeltaTime::Instance().GetDeltaTime());
	m_pPlayer.lock()->SetPos(_nowPos);

	//有効時間の管理
	if (m_cnt >= TIME)
	{
		//立ち状態に
		m_manager.lock()->ChangeAction("P_Air_Move");
	}
	else
	{
		m_cnt += DeltaTime::Instance().GetDeltaTime();
	}
	
	

}

void P_Air_Dash::ActionStart()
{
	m_moveVec = m_pPlayer.lock()->GetMatrix().Forward();
	m_moveVec.Normalize();

	m_cnt = 0.0;

	m_pPlayer.lock()->SetAnimation("Dash", true);
}

void P_Air_Dash::ActionReset()
{

}
