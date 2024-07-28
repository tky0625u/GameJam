#pragma once
#include"../../Action/ActionManager.h"

class Character;

class P_ActionManager :public ActionManager
{
public:
	P_ActionManager(){}
	virtual ~P_ActionManager() {}

	void Init()override;
	void Event()override;

	void SetPlayer(std::shared_ptr<Character> a_player) { m_player = a_player; }

private:

	std::weak_ptr<Character> m_player;

};
