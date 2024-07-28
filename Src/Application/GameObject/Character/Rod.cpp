#include "Rod.h"

#include"Character.h"

#include"Application/main.h"

void Rod::Init()
{
	if (!m_spModel)
	{
		m_spModel = std::make_shared<KdModelWork>();
		m_spModel->SetModelData("Asset/Models/Player/Rod.gltf");

		m_pCollider = std::make_unique<KdCollider>();
		m_pCollider->RegisterCollisionShape("Damage", m_spModel, KdCollider::TypeBump);
	}


}

void Rod::Update()
{
	

	Math::Matrix _trans = Math::Matrix::CreateTranslation(Math::Vector3(0,0,0));
	Math::Matrix _scale = Math::Matrix::CreateScale(100.0f);

	Math::Matrix _target = Math::Matrix::Identity;
	if (m_target.lock() != nullptr)
	{
		_target = m_target.lock()->GetWeaponMat();
	}



	m_mWorld = _scale*_trans*_target;

	Application::Instance().m_log.AddLog(":pos_x =%.2f", m_mWorld.Translation().x);
	Application::Instance().m_log.AddLog(":pos_y =%.2f", m_mWorld.Translation().y);
	Application::Instance().m_log.AddLog(":pos_z =%.2f\n", m_mWorld.Translation().z);
}

void Rod::DrawLit()
{
	if (!m_spModel) return;

	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel,m_mWorld);
}

