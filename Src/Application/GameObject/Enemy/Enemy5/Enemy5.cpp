#include "Enemy5.h"

void Enemy5::Init()
{
	if (!m_spModel)
	{
		m_spModel = std::make_shared<KdModelWork>();
		m_spModel->SetModelData("Asset/Models/enemy5/enemy5.gltf");

		m_pCollider = std::make_unique<KdCollider>();
		m_pCollider->RegisterCollisionShape("Hit", m_spModel, KdCollider::TypeDamage);

		//初期のアニメーションをセットする
		m_spAnimater = std::make_shared<KdAnimator>();
		m_spAnimater->SetAnimation(m_spModel->GetData()->GetAnimation("Idle"));
		
		m_mWorld = Math::Matrix::CreateTranslation(m_pos);

		m_Ani_Speed = 1.f;
		m_Speed = 0.25;
	}
}

void Enemy5::Update()
{
	
}

void Enemy5::PostUpdate()
{
	m_spAnimater->AdvanceTime(m_spModel->WorkNodes(),m_Ani_Speed);
	m_spModel->CalcNodeMatrices();
}

void Enemy5::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
}

void Enemy5::UpdateRotate(const Math::Vector3& srcMoveVec)
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
