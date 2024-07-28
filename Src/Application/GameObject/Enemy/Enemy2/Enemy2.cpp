#include "Enemy2.h"

void Enemy2::Init()
{
	m_model = std::make_shared<KdModelData>();
	m_model->Load("Asset/Models/enemy4/sandMan.gltf");

	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("HitObj1", m_model, KdCollider::TypeDamage);

}

void Enemy2::Update()
{

}

void Enemy2::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld);
}
