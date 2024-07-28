#include "Terrain.h"

void Terrain::Init()
{
	if (!m_spModel)
	{
		m_spModel = std::make_shared<KdModelData>();
		m_spModel->Load("Asset/Models/Beach/Beach.gltf");

		m_pCollider = std::make_unique<KdCollider>();
		m_pCollider->RegisterCollisionShape("Ground", m_spModel, KdCollider::TypeGround);
	}


	//m_pDebugWire = std::make_unique<KdDebugWireFrame>();
}

void Terrain::Update()
{
	///m_pDebugWire->AddDebugSphere(m_mWorld.Translation()+Math::Vector3{0,1.0f,0}, 0.5f, kGreenColor);
}

void Terrain::DrawLit()
{
	if (!m_spModel) return;

	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel,m_mWorld);
}

void Terrain::SetType(std::shared_ptr<KdModelData> a_spModel)
{
	m_spModel = a_spModel;

	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("Ground", m_spModel, KdCollider::TypeBump);
	//m_pCollider->RegisterCollisionShape("Ground", m_spModel, KdCollider::TypeGround);
	//m_pCollider->RegisterCollisionShape("EnemyCollision", { 0,0 + 1.0,0 }, 0.5f, KdCollider::Type::TypeGround);

}

