#include"../../../../P_ActionManager.h"
#include "P_Ground_Attack03.h"

#include"Application/GameObject/Entitys/Character/Player/player.h"

void P_Ground_Attack03::Init()
{
}

void P_Ground_Attack03::Update()
{

	//有効時間の管理
	if (m_cnt >= END_TIME)
	{
		//立ち状態に
		m_manager.lock()->ChangeAction("P_Ground_Stand");
	}
	//入力待機
	else if (m_cnt >= TIME)
	{
		//地上...移動
		if ((GetAsyncKeyState('D') & 0x8000) || (GetAsyncKeyState('A') & 0x8000) || (GetAsyncKeyState('W') & 0x8000) || (GetAsyncKeyState('S') & 0x8000))
		{
			m_manager.lock()->ChangeAction("P_Ground_Move");
		}

		//ジャンプ
		if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		{
			//ジャンプ状態にする
			m_pPlayer.lock()->SetJumpPow(-5.0f);
			m_manager.lock()->ChangeAction("P_Air_Move");

			//重力をかける////////////////////////////////////////////////////
			m_pPlayer.lock()->Grav();
			///////////////////////////////////////////////////////////////
		}

		//高速移動
		if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
		{
			m_manager.lock()->ChangeAction("P_Ground_Dash");
		}

		//攻撃1へ以降
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		{
			m_manager.lock()->ChangeAction("P_Ground_Attack01");
		}


		m_cnt += DeltaTime::Instance().GetDeltaTime();
	}
	else
	{
		m_cnt += DeltaTime::Instance().GetDeltaTime();
	}

	

}

void P_Ground_Attack03::ActionStart()
{
	KdEffekseerManager::GetInstance().Play("hit.efkefc", Math::Vector3(m_pPlayer.lock()->GetPos() + m_pPlayer.lock()->GetMatrix().Backward() * 5.0f + Math::Vector3(0, 1, 0)), 3.0f, 120, false);
	m_cnt = 0.0;

	m_pPlayer.lock()->SetAnimation("Attack", false);
}

void P_Ground_Attack03::ActionReset()
{
}
