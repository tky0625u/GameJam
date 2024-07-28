#include"../../../../P_ActionManager.h"
#include "P_Ground_Attack01.h"

#include"Application/GameObject/Character/Character.h"

void P_Ground_Attack01::Init()
{
}

void P_Ground_Attack01::Update()
{

	//有効時間の管理
	if (m_cnt >= END_TIME)
	{
		//立ち状態に
		m_manager.lock()->ChangeAction("P_Ground_Move");
	}
	//入力待機
	else if (m_cnt >= TIME)
	{
		//地上...移動
		if ((GetAsyncKeyState('D') & 0x8000) || (GetAsyncKeyState('A') & 0x8000) || (GetAsyncKeyState('W') & 0x8000) || (GetAsyncKeyState('S') & 0x8000))
		{
			m_manager.lock()->ChangeAction("P_Ground_Move");
		}

		m_cnt++;
	}
	else
	{
		m_cnt++;
	}

	if(m_cnt==10)
	{
		KdAudioManager::Instance().Play("Asset/Sounds/SE/bou-furu.wav", false);
	}



	if (!m_actionEndFlg && m_pPlayer.lock()->IsAnimEnd())
	{
		m_pPlayer.lock()->SetAnimation("Attack_After", false,1.5f);
		m_actionEndFlg = true;
	}

	

}

void P_Ground_Attack01::ActionStart()
{
	m_cnt = 0.0;
	m_actionEndFlg = false;

	m_pPlayer.lock()->SetAnimation("Attack", false, 1.5f);
}
	

void P_Ground_Attack01::ActionReset()
{
}
