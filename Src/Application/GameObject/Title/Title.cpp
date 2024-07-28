#include "Title.h"
#include"../../Scene/SceneManager.h"

void Title::Init()
{
	m_sptex = std::make_shared<KdTexture>();
	m_sptex->Load("Asset/Textures/Title/title.png");

	m_spentertex = std::make_shared<KdTexture>();
	m_spentertex->Load("Asset/Textures/Title/enter.png");

	m_spbluetex = std::make_shared<KdTexture>();
	m_spbluetex->Load("Asset/Textures/lightblue.png");

	//エンター文字画像
	m_enteralphaAdd = -0.02f;
	m_enteralpha = 1.0f;

	//青画像
	m_bluealphaAdd = -0.02f;//alpha値を増やすか減らすか
	m_bluealpha = 1.0f;		//blueの透明度
	m_bblue = true;			//blueの画像を出すか

	m_isReturn = true;
	m_isnextScene = false;

	//音
	m_sewave = KdAudioManager::Instance().Play("Asset/Sounds/SE/sea.wav", true);
	if (m_sewave.expired() == false)
	{
		m_sewave.lock()->SetVolume(m_wavevol);
	}

}

void Title::Update()
{

	//エンター文字画像の透明度を変える
	m_enteralpha += m_enteralphaAdd;

	if (m_enteralpha < 0.2f)
	{
		m_enteralpha = 0.2f;
		m_enteralphaAdd *= -1;
	}

	if (m_enteralpha > 1.0f)
	{
		m_enteralpha = 1.0f;
		m_enteralphaAdd *= -1;
	}


	//青画像の透明度を変える
	if (m_bblue)
	{
		m_bluealpha += m_bluealphaAdd;

		if (m_bluealpha < 0.0f)
		{
			m_bluealpha = 0.0f;
			m_bblue = false;
		}

		if (m_bluealpha > 1.0f)
		{
			m_bluealpha = 1.0f;
			m_bblue = false;
			m_isnextScene = true;
		}

	}


	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		if (!m_isReturn)
		{
			m_isReturn = true;
			if (!m_bblue)
			{
				m_sestart = KdAudioManager::Instance().Play("Asset/Sounds/SE/push.wav",false);
				if (m_sestart.expired() == false)
				{
					m_sestart.lock()->SetVolume(0.3f);
				}

				m_iswave = true;
				m_bblue = true;
				m_bluealphaAdd *= -1;
			}
		}
	}
	else
	{
		m_isReturn = false;
	}

	//音を下げる
	if (m_iswave)
	{
		m_wavevol -= 0.003f;
		if (m_sewave.expired() == false)
		{
			m_sewave.lock()->SetVolume(m_wavevol);
		}

		if (m_wavevol < 0)
		{
			m_sewave.lock()->Stop();
		}

	}

	if (m_isnextScene)
	{
		SceneManager::Instance().SetNextScene
		(
			SceneManager::SceneType::Game
		);
	}

}

void Title::DrawSprite()
{
	//タイトル文字画像
	Math::Color titlecolor = { 1.0f,1.0f,1.0f,m_enteralpha+0.5f };
	Math::Rectangle titlerc = { 0,0,(long)m_sptex->GetWidth(),(long)m_sptex->GetHeight() };
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_sptex, 0, 200, titlerc.width * 1.5f, titlerc.height * 1.5f, &titlerc, &titlecolor);

	//エンター文字画像
	Math::Color entercolor = { 1.0f,1.0f,1.0f,m_enteralpha };
	Math::Rectangle enterrc = { 0,0,(long)m_spentertex->GetWidth(),(long)m_spentertex->GetHeight() };
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_spentertex, 30, -100, enterrc.width * 1.3f, enterrc.height * 1.3f, &enterrc, &entercolor);

	//青画像
	Math::Color bluecolor = { 1.0f,1.0f,1.0f,m_bluealpha };
	Math::Rectangle bluerc = { 0,0,(long)m_spbluetex->GetWidth(),(long)m_spbluetex->GetHeight() };
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_spbluetex, 0, 0, bluerc.width, bluerc.height, &bluerc, &bluecolor);

}
