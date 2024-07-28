#include "Enemy6.h"
void Enemy6::Init()
{
	if (!m_spModel)
	{
		m_spModel = std::make_shared<KdModelWork>();
		m_spModel->SetModelData("Asset/Models/enemy3/enemy3.gltf");

		m_pCollider = std::make_unique<KdCollider>();
		m_pCollider->RegisterCollisionShape("Hit", m_spModel, KdCollider::TypeDamage);

		//初期のアニメーションをセットする
		m_spAnimater = std::make_shared<KdAnimator>();
		m_spAnimater->SetAnimation(m_spModel->GetData()->GetAnimation("Walk"));
		
		m_mWorld = Math::Matrix::CreateTranslation(m_pos);

		m_Ani_Speed = 1.f;

		float rand = KdGetFloat(0.7f, 1.0f);
		m_Speed = 0.05f*rand;


		angle = 0;
		isflg = false;

		m_dir = { 0,0,1 };

		m_moveRad = KdGetFloat(0.7f, 1.0f);
	}
}

void Enemy6::Update()
{
	if (m_dir.x > 0.5f)m_anglePlus = 90;
	if (m_dir.z > 0.5f)m_anglePlus = 0;
	
	Math::Vector3 lowerBound = {m_basePos.x -5.0f*m_moveRad,m_basePos.y+ 0.0f,m_basePos.z -5.0f * m_moveRad };
	Math::Vector3 upperBound = { m_basePos.x+ 5.0f * m_moveRad,m_basePos.y +0.0f,m_basePos.z+ 5.0f * m_moveRad };
	if (!isflg)
	{
		if (m_pos.x > upperBound.x || m_pos.x < lowerBound.x) {
			m_dir.x *= -1; // X軸方向を反転
			isflg = true;
		}
		if (m_pos.z > upperBound.z || m_pos.z < lowerBound.z) {
			m_dir.z *= -1;
			isflg = true;
		}
		// キャラクターの位置を更新
		m_pos += m_dir * m_Speed;
	}
	else
	{
		angle+=5;
		if (angle >= 180*cnt)
		{
			isflg = false;
			cnt++;
		}

		if (angle >= 360)
		{
			angle = 0;
			cnt = 1;
		}
		
	}

	Math::Matrix rotY = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(angle+180+m_anglePlus));

	Math::Matrix trans = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = rotY * trans;
}

void Enemy6::PostUpdate()
{
	m_spAnimater->AdvanceTime(m_spModel->WorkNodes(),m_Ani_Speed);
	m_spModel->CalcNodeMatrices();
}

void Enemy6::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
}

void Enemy6::UpdateRotate(const Math::Vector3& srcMoveVec)
{
	// 何も入力が無い場合は処理しない
	if (srcMoveVec.LengthSquared() == 0.0f) { return; }

	// キャラの正面方向のベクトル
	Math::Vector3 _nowDir = GetMatrix().Backward();

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
