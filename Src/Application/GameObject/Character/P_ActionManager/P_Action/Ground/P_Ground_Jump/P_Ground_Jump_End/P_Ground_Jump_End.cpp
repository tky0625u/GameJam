#include"../../../../P_ActionManager.h"
#include "P_Ground_Jump_End.h"

#include"Application/GameObject/Entitys/Character/Player/player.h"

void P_Ground_Jump_End::Init()
{
}

void P_Ground_Jump_End::Update()
{
	if (m_pPlayer.lock()->IsAnimEnd())
	{
		m_manager.lock()->ChangeAction("P_Ground_Stand");
	}

	//重力をかける////////////////////////////////////////////////////
	m_pPlayer.lock()->Grav();
	///////////////////////////////////////////////////////////////
}

void P_Ground_Jump_End::ActionStart()
{
	m_pPlayer.lock()->SetAnimation("Jump_End", false);
}

void P_Ground_Jump_End::ActionReset()
{
}
 