#include "Character.h"

#include "../../main.h"
#include "../Camera/CameraBase.h"

#include"../UI/Life/Life.h"
#include"../../Scene/SceneManager.h"

#include"P_ActionManager/P_ActionManager.h"

void Character::Init()
{
	if (!m_spModel)
	{	
		m_spModel = std::make_shared<KdModelWork>();
		m_spModel->SetModelData("Asset/Models/Player/player.gltf");

	/*	m_spModel = std::make_shared<KdModelWork>();
		m_spModel->SetModelData("Asset/Models/tank/tank.gltf");*/

		//初期のアニメーションをセットする
		m_spAnimater = std::make_shared<KdAnimator>();
		m_spAnimater->SetAnimation(m_spModel->GetData()->GetAnimation("Idle"));
	}

	//行動管理クラスの作成
	m_actionManager = std::make_shared<P_ActionManager>();
	m_actionManager->SetPlayer(shared_from_this());
	m_actionManager->Init();


	//SetPos(Math::Vector3(0, 0, 45));

	m_isEffekseer = false;

	//HP
	m_life = 3;
	//無敵
	m_ismuteki = false;
	m_mutekiframe = 0;

	m_alpha = 1.0f;		//エンター画像の透明度を変える
	m_alphaAdd = -0.03f;	//エンター画像の透明度の増減値

	m_isdeath = false;	//死亡したか
	m_deathframe = 0;	//死亡後何秒後にリセットするか

	// キャラクターのワールド行列を創る処理
	m_worldRot.y = 180;

	Math::Matrix _scale = Math::Matrix::CreateScale(100.0f);
	Math::Matrix _rotation = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_worldRot.y));
	m_mWorld = _scale * _rotation * Math::Matrix::CreateTranslation(GetPos());


	m_pDebugWire = std::make_unique<KdDebugWireFrame>();
}

void Character::Update()
{
	if (GetAsyncKeyState('M') & 0x8000)
	{
		m_hitFlg = true;
	}
	else
	{
		m_keyFlg = false;
	}

	//アクションの更新
	if(m_moveFLg)m_actionManager->Update();

	//// キャラクターの移動速度(真似しちゃダメですよ)
	//float			_moveSpd = 0.05f;
	//Math::Vector3	_nowPos	= GetPos();

	//Math::Vector3 _moveVec = Math::Vector3::Zero;
	//if (GetAsyncKeyState('D')) { _moveVec.x =  1.0f; }
	//if (GetAsyncKeyState('A')) { _moveVec.x = -1.0f; }
	//if (GetAsyncKeyState('W')) { _moveVec.z =  1.0f; }
	//if (GetAsyncKeyState('S')) { _moveVec.z = -1.0f; }

	//const std::shared_ptr<const CameraBase> _spCamera = m_wpCamera.lock();
	//if (_spCamera)
	//{
	//	_moveVec = _moveVec.TransformNormal(_moveVec, _spCamera->GetRotationYMatrix());
	//}
	//_moveVec.Normalize();
	//_moveVec *= _moveSpd;
	//_nowPos += _moveVec;

	//// キャラクターの回転行列を創る
	//UpdateRotate(_moveVec);

	//=========================================================================
	//死亡時に透明度を変える
	if (m_isdeath)
	{
		m_alpha += m_alphaAdd;
		m_deathframe++;

		if (m_alpha > 1)
		{
			m_alpha = 1.0f;
			m_alphaAdd *= -1;

			if (m_deathframe > 60)
			{
				m_alphaAdd = -0.08f;
			}

		}
		if (m_alpha < 0.2f)
		{
			m_alpha = 0.2f;
			m_alphaAdd *= -1;

			if (m_deathframe > 60)
			{
				m_alphaAdd = 0.08f;
			}

		}

		if (m_deathframe > 120)
		{
			//SetPos(Math::Vector3(0, 0, 0));
			m_life = 3;
			m_isdeath = false;
			m_deathframe = 0;
			m_alpha = 1.0f;
			m_alphaAdd = -0.03f;

		}

	}

	//無敵にする
	if (m_ismuteki)
	{
		m_mutekiframe++;

		if (m_mutekiframe > 90)
		{
			m_ismuteki = false;
			m_mutekiframe = 0;
		}
	}

	//if (m_isdeath)return;

	OnHit();

	//=========================
	//球判定
	//=========================
	Math::Vector3 _nowPos = m_mWorld.Translation();

	//球判定用の変数作成
	KdCollider::SphereInfo sphere;
	//球の中心点を設定
	sphere.m_sphere.Center = (_nowPos + Math::Vector3{0, 0.5f, 0});
	//球の半径を設定
	sphere.m_sphere.Radius = 0.3f;


	//当たり判定をしたいタイプを設定
	sphere.m_type = KdCollider::TypeGround|KdCollider::TypeBump;

	//デバッグ標示
	//m_pDebugWire->AddDebugSphere(sphere.m_sphere.Center, sphere.m_sphere.Radius);

	//弾に当たったリスト
	std::list<KdCollider::CollisionResult> retSphereList;

	//当たり判定!!!!!!!!!!!!!!!!!!
		//レイと当たり判定!!
	for (auto& obj : SceneManager::Instance().GetObjList())
	{
		obj->Intersects(sphere, &retSphereList);

	}

	//レイに当たったリストから一番近いオブジェクトを検出
	float maxOverLap = 0;	//はみ出たレイの長さ
	Math::Vector3 hitDir;	//レイが遮断された座標(当たっている場所)
	bool isHit = false;		//当たっていたらtrueになる


	for (auto& ret : retSphereList)
	{
		//球にめり込んで、オーバーした長さが一番長いものを探す
		if (maxOverLap < ret.m_overlapDistance)
		{
			maxOverLap = ret.m_overlapDistance;
			hitDir = ret.m_hitDir;
			isHit = true;

		}

	}

	if (isHit)
	{
		////zへの押し返し無効
		//hitDir.y = 0;
		//正規化(長さを一にする)
		hitDir.Normalize();


		//地面に当たっている
		//m_pos += hitDir * maxOverLap;
		_nowPos+=hitDir * maxOverLap;
	}


	if (_nowPos.x > 15)
	{
		_nowPos.x = 15;
	}
	if (_nowPos.x < -13)
	{
		_nowPos.x = -13;
	}
	if (_nowPos.z < -2)
	{
		_nowPos.z = -2;
	}


	// キャラクターのワールド行列を創る処理
	Math::Matrix _scale = Math::Matrix::CreateScale(100.0f);
	Math::Matrix _rotation = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_worldRot.y));
	m_mWorld = _scale*_rotation * Math::Matrix::CreateTranslation(_nowPos);




}

void Character::PostUpdate()
{
	//アニメーションの更新処理
	m_spAnimater->AdvanceTime(m_spModel->WorkNodes(),m_animSpeed);
	m_spModel->CalcNodeMatrices();


	//OnHit();
}

void Character::DrawLit()
{
	if (!m_spModel) return;
	KdShaderManager::Instance().ChangeRasterizerState(KdRasterizerState::CullNone);

	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld,Math::Color(1,1,1,m_alpha));

	KdShaderManager::Instance().ChangeRasterizerState(KdRasterizerState::CullBack);
}

void Character::DrawUnLit()
{

}

void Character::UpdateRotate(const Math::Vector3& srcMoveVec)
{
	// 何も入力が無い場合は処理しない
	if (srcMoveVec.LengthSquared() == 0.0f) { return; }

	// キャラの正面方向のベクトル
	Math::Vector3 _nowDir = GetMatrix().Forward();

	// 移動方向のベクトル
	Math::Vector3 _targetDir = srcMoveVec;

	_nowDir.Normalize();
	_targetDir.Normalize();

	float _nowAng = atan2(_nowDir.x, _nowDir.z);
	_nowAng = DirectX::XMConvertToDegrees(_nowAng);

	float _targetAng = atan2(_targetDir.x, _targetDir.z);
	_targetAng = DirectX::XMConvertToDegrees(_targetAng);

	// 角度の差分を求める
	float _betweenAng = _targetAng - _nowAng;
	if (_betweenAng > 180)
	{
		_betweenAng -= 360;
	}
	else if (_betweenAng < -180)
	{
		_betweenAng += 360;
	}

	float rotateAng = std::clamp(_betweenAng, -8.0f, 8.0f);
	m_worldRot.y += rotateAng;
}


void Character::OnHit()
{
	//=========================
	//球判定
	//=========================
	Math::Vector3 _nowPos = m_mWorld.Translation();

	//球判定用の変数作成
	KdCollider::SphereInfo sphere;
	//球の中心点を設定
	sphere.m_sphere.Center = (_nowPos + Math::Vector3{ 0, 0.5f, 0 });
	//球の半径を設定
	sphere.m_sphere.Radius = 0.5f;


	//当たり判定をしたいタイプを設定
	sphere.m_type = KdCollider::TypeDamage;

	//デバッグ標示
	//m_pDebugWire->AddDebugSphere(sphere.m_sphere.Center, sphere.m_sphere.Radius);

	//弾に当たったリスト
	std::list<KdCollider::CollisionResult> retSphereList;

	//当たり判定!!!!!!!!!!!!!!!!!!
		//レイと当たり判定!!
	for (auto& obj : SceneManager::Instance().GetObjList())
	{
		if (obj->Intersects(sphere, &retSphereList))
		{
			if (!m_hitFlg)
			{
				m_isdeath = true;
				SetPos(Math::Vector3(0, 0, 0));

				KdEffekseerManager::GetInstance().Play("warp.efkefc", GetPos() + Math::Vector3(0, 1.0f, 0), 1.0f, 1, false);
				KdAudioManager::Instance().Play("Asset/Sounds/SE/warp_after.wav", false);
				return;
			}
		}

	}
}