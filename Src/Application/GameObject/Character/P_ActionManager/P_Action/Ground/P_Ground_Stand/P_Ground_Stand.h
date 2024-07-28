#pragma once
#include"../../P_ActionBase.h"

class Character;

class P_Ground_Stand :public P_ActionBase
{
public:
	P_Ground_Stand(std::weak_ptr<Character> a_owner, std::shared_ptr<ActionManager> a_manager) :P_ActionBase(a_owner, a_manager) {}
	~P_Ground_Stand() {}

	void Init()override;
	void Update()override;

	void ActionStart()override;
	void ActionReset()override;

private:

};
