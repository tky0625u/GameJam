#include"../../../../P_ActionManager.h"
#include "P_Ground_Move.h"

#include"Application/main.h"
#include"Application/Scene/SceneManager.h"
#include"Application/Scene/BaseScene/BaseScene.h"
#include"Application/GameObject/Camera/CameraBase.h"


#include"Application/GameObject/Character/Character.h"

void P_Ground_Move::Init()
{
}

void P_Ground_Move::Update()
{
	// キャラクターの移動
	//////////////////////////////////////////////////////////////////////
	Math::Vector3 _nowPos = m_pPlayer.lock()->GetPos();

	Math::Vector3 _moveVec = Math::Vector3::Zero;

	//前に移動し続ける
	_moveVec.z += 1.0f;



	//マウスで指定した方向へ移動///////////////////////////////
	if (GetAsyncKeyState(MK_LBUTTON) & 0x8000)
	{
		POINT m_mouse;
		GetCursorPos(&m_mouse);
		ScreenToClient(Application::Instance().GetWindowHandle(), &m_mouse);


		Math::Vector3 pos;
		Math::Vector3 move;
		float m_moveReng = 0;

		SceneManager::Instance().GetScene()->GetCamera().lock()->GetCamera()->GenerateRayInfoFromClientPos(m_mouse, pos, move, m_moveReng);

		//===========================
		//当たり判定(レイ判定)
		//===========================

		//レイ判定用に変数を作成
		KdCollider::RayInfo ray;

		//レイの発射(座標)位置
		ray.m_pos = pos;//自分の足元

		//レイの発射方向を設定
		ray.m_dir = move;


		//レイの長さを設定
		ray.m_range = m_moveReng;

		//当たり判定をしたいタイプ
		ray.m_type = KdCollider::Type::TypeGround;

		//レイに当たったオブジェクト情報を格納するリストを作る
		std::list<KdCollider::CollisionResult> retRayList;
		//レイと当たり判定!!
		for (auto& obj : SceneManager::Instance().GetObjList())
		{
			obj->Intersects(ray, &retRayList);

		}

		//レイに当たったリストから一番近いオブジェクトを検出
		float maxOverLap = 0;	//はみ出たレイの長さ
		Math::Vector3 hitPos;	//レイが遮断された座標(当たっている場所)
		bool isHit = false;		//当たっていたらtrueになる

		for (auto& ret : retRayList)
		{
			//レイを遮断し、オーバーした長さが一番長いものを探す
			if (maxOverLap < ret.m_overlapDistance)
			{
				maxOverLap = ret.m_overlapDistance;
				hitPos = ret.m_hitPos;
				isHit = true;

			}

		}

		if (isHit)
		{
			//地面に当たっている
			pos = hitPos;
		}

		Math::Vector3 _vec = pos-_nowPos ;
		_vec.Normalize();
		
		_vec.y = 0;

		m_moveVec = _vec;
		//m_moveVec = _moveVec = _moveVec.TransformNormal(_moveVec, _spCamera->GetRotationYMatrix());
	}



	m_pPlayer.lock()->UpdateRotate(m_moveVec);

	//////////////////////////////////////////////////////////////
	// 回転制御

	//_moveVec.Normalize();
	////カメラ方向に移動
	//m_pPlayer.lock()->UpdateRotate(_moveVec);

	if (!m_actionEndFlg)
	{
		//かそくする
		if (m_moveSpeed < 0.02f)
		{
			m_moveSpeed += 0.001f;

			if (m_moveSpeed > 0.02f)
			{
				m_moveSpeed = 0.02f;
			}
		}
		
	}


	//移動する
	_nowPos += m_moveVec * m_moveSpeed;
	m_pPlayer.lock()->SetPos(_nowPos);


	//攻撃1へ以降
	if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
	{
		m_manager.lock()->ChangeAction("P_Ground_Attack01");
	}


	if (!m_actionEndFlg && m_pPlayer.lock()->IsAnimEnd())
	{
		m_pPlayer.lock()->SetAnimation("Move", true,0.8f);
		m_actionEndFlg = true;
	}

}

void P_Ground_Move::ActionStart()
{
	m_pPlayer.lock()->SetAnimation("Move_Before", false,0.7f);

	m_actionEndFlg = false;

	m_moveSpeed = 0.0f;

	m_moveVec = { 0,0,1 };

	if (m_move.expired())
	{
		m_move = KdAudioManager::Instance().Play("Asset/Sounds/SE/sunahama-asioto-hidari.wav", true);
		m_move.lock()->SetVolume(0.2f);
	}

	if (m_move.lock()->IsStopped())
	{
		m_move = KdAudioManager::Instance().Play("Asset/Sounds/SE/sunahama-asioto-hidari.wav", true);
		m_move.lock()->SetVolume(0.2f);
	}
}

void P_Ground_Move::ActionReset()
{
	m_move.lock()->Stop();
}
