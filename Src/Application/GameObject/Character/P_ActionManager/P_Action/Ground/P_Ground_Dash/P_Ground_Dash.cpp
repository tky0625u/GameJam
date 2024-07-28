#include"../../../P_ActionManager.h"
#include "P_Ground_Dash.h"

#include"Application/GameObject/Entitys/Character/Player/player.h"

void P_Ground_Dash::Init()
{
	//クールタイムの設定
	m_coolTime = 1.0;
}

void P_Ground_Dash::Update()
{
	// キャラクターの移動
	//////////////////////////////////////////////////////////////////////
	Math::Vector3 _nowPos = m_pPlayer.lock()->GetPos();

	//Math::Vector3 _moveVec = Math::Vector3::Zero;


	//_moveVec.Normalize();
	////カメラ方向に移動
	//m_pPlayer.lock()->GetCamVec(_moveVec);

	//移動する
	_nowPos += m_moveVec * (m_moveSpeed * DeltaTime::Instance().GetDeltaTime());
	m_pPlayer.lock()->SetPos(_nowPos);

	//有効時間の管理
	if (m_cnt >= TIME)
	{
		//立ち状態に
		m_manager.lock()->ChangeAction("P_Ground_Stand");
	}
	else
	{
		m_cnt += DeltaTime::Instance().GetDeltaTime();
	}
	
	

}

void P_Ground_Dash::ActionStart()
{
	m_moveVec = m_pPlayer.lock()->GetMatrix().Forward();
	m_moveVec.Normalize();
	m_cnt = 0.0;

	m_pPlayer.lock()->SetAnimation("Dash", true);
}

void P_Ground_Dash::ActionReset()
{

}
