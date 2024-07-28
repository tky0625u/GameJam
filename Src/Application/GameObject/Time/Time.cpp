#include "Time.h"

void Time::Init()
{
	m_pzero = std::make_shared<KdTexture>();
	m_pzero->Load("Asset/Textures/Score/zero.png");

	m_pone = std::make_shared<KdTexture>();
	m_pone->Load("Asset/Textures/Score/one.png");

	m_ptwo = std::make_shared<KdTexture>();
	m_ptwo->Load("Asset/Textures/Score/two.png");

	m_pthree = std::make_shared<KdTexture>();
	m_pthree->Load("Asset/Textures/Score/three.png");

	m_pfour = std::make_shared<KdTexture>();
	m_pfour->Load("Asset/Textures/Score/four.png");

	m_pfive = std::make_shared<KdTexture>();
	m_pfive->Load("Asset/Textures/Score/five.png");

	m_psix = std::make_shared<KdTexture>();
	m_psix->Load("Asset/Textures/Score/six.png");

	m_pseven = std::make_shared<KdTexture>();
	m_pseven->Load("Asset/Textures/Score/seven.png");

	m_peight = std::make_shared<KdTexture>();
	m_peight->Load("Asset/Textures/Score/eight.png");

	m_pnine = std::make_shared<KdTexture>();
	m_pnine->Load("Asset/Textures/Score/nine.png");

	m_pcoron = std::make_shared<KdTexture>();
	m_pcoron->Load("Asset/Textures/Score/coron.png");

	m_time = 0;				//何秒経ったか
	m_onetime = 0;			//1の位
	m_tentime = 0;			//10の位
	m_hundredtime = 0;		//100の位

	m_isstart = true;		//カウントダウンが終わるまでは進めない
	m_isgoal = false;		//ゴールしたら止める

}

void Time::Update()
{

	if (m_isstart)return;
	if (m_isgoal)return;
	m_time++;

	if (m_time >= 60)
	{
		m_time = 0;
		m_onetime++;

		if (m_onetime >= 10)
		{
			m_onetime = 0;
			m_tentime++;

			if (m_tentime >= 6)
			{
				m_hundredtime++;
				m_tentime = 0;
				
				if (m_hundredtime >= 6)
				{
					m_thousandtime++;
					m_hundredtime = 0;
				}
			}

		}

	}

	

}

void Time::DrawSprite()
{
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_pcoron, -395, 300);
	OneTime();
	TenTime();
	HundredTime();
	ThousandTime();

}

void Time::OneTime()
{
	int x = -250;
	int y = 300;

	switch (m_onetime)
	{
	case 0:
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_pzero, x, y);
		break;
	case 1:
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_pone, x, y);
		break;
	case 2:
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_ptwo, x, y);
		break;
	case 3:
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_pthree, x, y);
		break;
	case 4:
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_pfour, x, y);
		break;
	case 5:
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_pfive, x, y);
		break;
	case 6:
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_psix, x, y);
		break;
	case 7:
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_pseven, x, y);
		break;
	case 8:
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_peight, x, y);
		break;
	case 9:
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_pnine, x, y);
		break;
	default:
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_pzero, x, y);
		break;
	}
}

void Time::TenTime()
{
	int x = -330;
	int y = 300;

	switch (m_tentime)
	{
	case 0:
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_pzero, x, y);
		break;
	case 1:
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_pone, x, y);
		break;
	case 2:
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_ptwo, x, y);
		break;
	case 3:
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_pthree, x, y);
		break;
	case 4:
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_pfour, x, y);
		break;
	case 5:
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_pfive, x, y);
		break;
	case 6:
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_psix, x, y);
		break;
	case 7:
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_pseven, x, y);
		break;
	case 8:
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_peight, x, y);
		break;
	case 9:
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_pnine, x, y);
		break;
	default:
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_pzero, x, y);
		break;
	}
}

void Time::HundredTime()
{
	int x = -460;
	int y = 300;

	switch (m_hundredtime)
	{
	case 0:
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_pzero, x, y);
		break;
	case 1:
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_pone, x, y);
		break;
	case 2:
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_ptwo, x, y);
		break;
	case 3:
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_pthree, x, y);
		break;
	case 4:
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_pfour, x, y);
		break;
	case 5:
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_pfive, x, y);
		break;
	case 6:
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_psix, x, y);
		break;
	case 7:
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_pseven, x, y);
		break;
	case 8:
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_peight, x, y);
		break;
	case 9:
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_pnine, x, y);
		break;
	default:
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_pzero, x, y);
		break;
	}
}

void Time::ThousandTime()
{
	int x = -540;
	int y = 300;

	switch (m_thousandtime)
	{
	case 0:
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_pzero, x, y);
		break;
	case 1:
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_pone, x, y);
		break;
	case 2:
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_ptwo, x, y);
		break;
	case 3:
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_pthree, x, y);
		break;
	case 4:
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_pfour, x, y);
		break;
	case 5:
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_pfive, x, y);
		break;
	case 6:
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_psix, x, y);
		break;
	case 7:
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_pseven, x, y);
		break;
	case 8:
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_peight, x, y);
		break;
	case 9:
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_pnine, x, y);
		break;
	default:
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_pzero, x, y);
		break;
	}
}
