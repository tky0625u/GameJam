#include "P_ActionManager.h"
#include"Application/main.h"

#include"P_Action/Ground/P_Ground_Stand/P_Ground_Stand.h"
#include"P_Action/Ground/P_Ground_Move/P_Ground_Move/P_Ground_Move.h"
//#include"P_Action/Ground/P_Ground_Move/P_Ground_Move_Start/P_Ground_Move_Start.h"
//#include"P_Action/Ground/P_Ground_Move/P_Ground_Move_End/P_Ground_Move_End.h"


#include"P_Action/Ground/P_Ground_Attack/P_Ground_Attack01/P_Ground_Attack01.h"
//#include"P_Action/Ground/P_Ground_Attack/P_Ground_Attack02/P_Ground_Attack02.h"
//#include"P_Action/Ground/P_Ground_Attack/P_Ground_Attack03/P_Ground_Attack03.h"


void P_ActionManager::Init()
{
	//アクションを登録する
	if (m_player.lock() != nullptr)
	{
		////////////////////////////////////////////////////////////////////
		//地面...通常
		std::shared_ptr<P_Ground_Stand> _ground_stand = std::make_shared<P_Ground_Stand>(m_player, shared_from_this());
		_ground_stand->Init();
		RegisterAction("P_Ground_Stand", _ground_stand);

		//地面..移動
		std::shared_ptr<P_Ground_Move> _ground_move = std::make_shared<P_Ground_Move>(m_player, shared_from_this());
		_ground_move->Init();
		RegisterAction("P_Ground_Move", _ground_move);


		//地面..攻撃１
		std::shared_ptr<P_Ground_Attack01> _ground_attack01 = std::make_shared<P_Ground_Attack01>(m_player, shared_from_this());
		_ground_attack01->Init();
		RegisterAction("P_Ground_Attack01", _ground_attack01);

	}

	ChangeAction("P_Ground_Stand");

}

void P_ActionManager::Event()
{
	//現在のアクションを出力
	Application::Instance().m_log.AddLog(m_currentActionName.data());
	Application::Instance().m_log.AddLog("\n");
}

