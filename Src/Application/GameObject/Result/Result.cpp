#include "Result.h"
#include"../../Scene/SceneManager.h"

void Result::Init()
{
	m_spWatermellonModel = std::make_shared<KdModelData>();
	m_spWatermellonModel->Load("Asset/Models/SmallWatermelon/smallwatermellon.gltf");

	m_sptex = std::make_shared<KdTexture>();
	m_sptex->Load("Asset/Textures/Result/result.png");

	m_spbluetex = std::make_shared<KdTexture>();
	m_spbluetex->Load("Asset/Textures/lightblue.png");

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

	m_prank = std::make_shared<KdTexture>();
	m_prank->Load("Asset/Textures/Rank/rank.png");

	m_pSrank = std::make_shared<KdTexture>();
	m_pSrank->Load("Asset/Textures/Rank/s.png");

	m_pArank = std::make_shared<KdTexture>();
	m_pArank->Load("Asset/Textures/Rank/a.png");

	m_pBrank = std::make_shared<KdTexture>();
	m_pBrank->Load("Asset/Textures/Rank/b.png");

	m_pCrank = std::make_shared<KdTexture>();
	m_pCrank->Load("Asset/Textures/Rank/c.png");

	m_bluealphaAdd = -0.02f;//alpha値を増やすか減らすか
	m_bluealpha = 1.0f;		//blueの透明度
	m_bblue = true;			//blueの画像を出すか

	m_isReturn = true;
	m_isnextScene = false;

	m_onetime = SceneManager::Instance().GetOneTime();
	m_tentime = SceneManager::Instance().GetTenTime();
	m_hundredtime = SceneManager::Instance().GetHundredTime();
	m_thousandtime = SceneManager::Instance().GetThousandTime();

	m_resultalpha = 1.0f;
	m_resultalphaAdd = -0.008f;

	m_rankalpha = 1.0f;
	m_rankalphaAdd = -0.008f;

}

void Result::Update()
{
	//青画像の透明度を変える
	if (m_bblue)
	{
		m_bluealpha += m_bluealphaAdd;

		if (m_bluealpha < 0.0f)
		{
			m_bblue = false;
		}

		if (m_bluealpha > 1.0f)
		{
			m_bluealpha = 1.0f;
			m_bblue = false;
			m_isnextScene = true;
		}

	}

	//リザルト文字
	m_resultalpha += m_resultalphaAdd;
	if (m_resultalpha < 0.8f)
	{
		m_resultalpha = 0.8f;
		m_resultalphaAdd *= -1;
	}

	if (m_resultalpha > 1.0f)
	{
		m_resultalpha = 1.0f;
		m_resultalphaAdd *= -1;
	}

	//ランク文字
	m_rankalpha += m_rankalphaAdd;
	if (m_rankalpha < 0.8f)
	{
		m_rankalpha = 0.8f;
		m_rankalphaAdd *= -1;
	}

	if (m_rankalpha > 1.0f)
	{
		m_rankalpha = 1.0f;
		m_rankalphaAdd *= -1;
	}


	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		if (!m_isReturn)
		{
			m_isReturn = true;
			if (!m_bblue)
			{
				m_bblue = true;
				m_bluealphaAdd *= -1;
			}
		}
	}
	else
	{
		m_isReturn = false;
	}

	if (m_isnextScene)
	{
		KdAudioManager::Instance().StopAllSound();
		SceneManager::Instance().SetNextScene
		(
			SceneManager::SceneType::Title
		);
	}

}

void Result::DrawSprite()
{

	//リザルト文字画像
	Math::Color resultcolor = { 1.0f,1.0f,1.0f,1.0f };
	Math::Rectangle resultrc = { 0,0,(long)m_sptex->GetWidth(),(long)m_sptex->GetHeight() };
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_sptex, 0, 200, resultrc.width*m_resultalpha, resultrc.height*m_resultalpha, &resultrc, &resultcolor);


	KdShaderManager::Instance().m_spriteShader.DrawTex(m_pcoron,25, 0);

	OneTime();
	TenTime();
	HundredTime();
	ThousandTime();

	//ランク文字
	Math::Color rankcolor = { 1.0f,1.0f,1.0f,1.0f };
	Math::Rectangle rankrc = { 0,0,(long)m_prank->GetWidth(),(long)m_prank->GetHeight() };
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_prank, -100, -150, rankrc.width, rankrc.height, &rankrc, &rankcolor);

	//何ランクか
	if (m_hundredtime == 0)
	{
		//S
		Math::Color scolor = { 1.0f,1.0f,1.0f,1.0f };
		Math::Rectangle src = { 0,0,(long)m_pSrank->GetWidth(),(long)m_pSrank->GetHeight() };
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_pSrank, 100, -150, src.width * m_rankalpha, src.height * m_rankalpha, &src, &scolor);
	}
	else if (m_onetime<=9 && m_tentime <= 2 && m_hundredtime == 1)
	{
		//A
		Math::Color acolor = { 1.0f,1.0f,1.0f,1.0f };
		Math::Rectangle arc = { 0,0,(long)m_pArank->GetWidth(),(long)m_pArank->GetHeight() };
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_pArank, 100, -150, arc.width * m_rankalpha, arc.height * m_rankalpha, &arc, &acolor);
	}
	else if (m_tentime <= 6 && m_hundredtime == 1 || m_hundredtime == 2 && m_tentime == 0)
	{
		//B
		Math::Color bcolor = { 1.0f,1.0f,1.0f,1.0f };
		Math::Rectangle brc = { 0,0,(long)m_pBrank->GetWidth(),(long)m_pBrank->GetHeight() };
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_pBrank, 100, -150, brc.width * m_rankalpha, brc.height * m_rankalpha, &brc, &bcolor);
	}
	else
	{
		//C
		Math::Color ccolor = { 1.0f,1.0f,1.0f,1.0f };
		Math::Rectangle crc = { 0,0,(long)m_pCrank->GetWidth(),(long)m_pCrank->GetHeight() };
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_pCrank, 100, -150, crc.width * m_rankalpha, crc.height * m_rankalpha, &crc, &ccolor);
	}


	//青画像
	Math::Color bluecolor = { 1.0f,1.0f,1.0f,m_bluealpha };
	Math::Rectangle bluerc = { 0,0,(long)m_spbluetex->GetWidth(),(long)m_spbluetex->GetHeight() };
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_spbluetex, 0, 0, bluerc.width, bluerc.height, &bluerc, &bluecolor);

	

}

void Result::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spWatermellonModel, m_mWorld);
}

void Result::OneTime()
{
	int x = 170;
	int y = 0;

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

void Result::TenTime()
{
	int x = 90;
	int y = 0;

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

void Result::HundredTime()
{
	int x = -55;
	int y = 0;

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

void Result::ThousandTime()
{
	int x = -135;
	int y = 0;

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
