#include"../../../P_ActionManager.h"
#include "P_Ground_Stand.h"

#include"Application/GameObject/Character/Character.h"

void P_Ground_Stand::Init()
{
}

void P_Ground_Stand::Update()
{
	//地上...移動
	/*if ((GetAsyncKeyState('D')&0x8000) || (GetAsyncKeyState('A')&0x8000) || (GetAsyncKeyState('W')&0x8000) || (GetAsyncKeyState('S')&0x8000)) 
	{
		m_manager.lock()->ChangeAction("P_Ground_Move");
	}*/

	if (m_pPlayer.lock()->GetStart())
	{
		m_manager.lock()->ChangeAction("P_Ground_Move");
	}

	//攻撃1へ以降
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		m_manager.lock()->ChangeAction("P_Ground_Attack01");
	}


}

void P_Ground_Stand::ActionStart()
{
	m_pPlayer.lock()->SetAnimation("Idle", true);
}

void P_Ground_Stand::ActionReset()
{
}
