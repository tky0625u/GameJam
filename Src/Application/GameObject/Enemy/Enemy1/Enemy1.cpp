#include "Enemy1.h"

void Enemy1::Init()
{
	m_model = std::make_shared<KdModelData>();
	m_model->Load("Asset/Models/enemy1/enemy1.gltf");

	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("HitObj1", m_model, KdCollider::TypeDamage);

}

void Enemy1::Update()
{

}

void Enemy1::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld);
}
