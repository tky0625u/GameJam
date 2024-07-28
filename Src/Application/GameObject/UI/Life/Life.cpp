#include "Life.h"

void Life::Init()
{
	m_ptex = std::make_shared<KdTexture>();
	m_ptex->Load("Asset/Textures/UI/Life.png");

	m_pos = {};

	m_objectType = KdGameObject::HP;

}

void Life::Update()
{

}

void Life::DrawSprite()
{
	//ハート画像
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_ptex, m_pos.x, m_pos.y);
}

void Life::OnHit()
{
	m_isExpired = true;
}
