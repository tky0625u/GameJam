#include "Start.h"
#include"../Time/Time.h"
#include"../Character/Character.h"

void Start::Init()
{
	m_sponeTex = std::make_shared<KdTexture>();
	m_sptwoTex = std::make_shared<KdTexture>();
	m_spthreeTex = std::make_shared<KdTexture>();
	m_spstartTex = std::make_shared<KdTexture>();

	m_sponeTex->Load("Asset/Textures/START/one.png");
	m_sptwoTex->Load("Asset/Textures/START/two.png");
	m_spthreeTex->Load("Asset/Textures/START/three.png");
	m_spstartTex->Load("Asset/Textures/START/start.png");

	m_secountdown = KdAudioManager::Instance().Play("Asset/Sounds/SE/countdown.wav");
	if (m_secountdown.expired() == false)
	{
		m_secountdown.lock()->SetVolume(0.2f);
	}

}

void Start::Update()
{
	m_countframe++;

	if (m_countframe >= 60)
	{
		m_countframe = 0;
		m_count++;
	}

	if (m_count >= 3)
	{
		if (!m_wptime.expired())
		{
			m_wptime.lock()->SetStart(false);
		}

		if (!m_wpplayer.expired())
		{
			m_wpplayer.lock()->SetStart(true);
		}

		if (m_countframe >= 30)
		{
			m_isExpired = true;

		}

	}

}

void Start::DrawSprite()
{
	if (m_count == 0)
	{
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_spthreeTex, 0, 150);
	}
	else if (m_count == 1)
	{
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_sptwoTex, 0, 150);
	}
	else if (m_count == 2)
	{
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_sponeTex, 0, 150);
	}
	else if (m_count == 3)
	{
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_spstartTex, 0, 150);
	}


}
