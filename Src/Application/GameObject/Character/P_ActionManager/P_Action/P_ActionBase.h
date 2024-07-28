#pragma once
#include"Application/GameObject/Action/ActionBase.h"

class Character;

class P_ActionBase :public ActionBase
{
public:
	P_ActionBase(std::weak_ptr<Character> a_owner, std::shared_ptr<ActionManager> a_manager) :ActionBase(a_manager) { m_pPlayer = a_owner; }
	virtual ~P_ActionBase() {}

	virtual void Init()override {};
	virtual void Update()override {};

	virtual void ActionStart()override {};
	virtual void ActionReset()override {};

protected:

	std::weak_ptr<Character> m_pPlayer;


};
