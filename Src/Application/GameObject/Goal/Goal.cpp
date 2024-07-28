#include "Goal.h"
#include"../Character/Character.h"
#include"../Time/Time.h"
#include"../../Scene/SceneManager.h"

void Goal::Init()
{
	m_spModel = std::make_shared<KdModelData>();
	m_spModel->Load("Asset/Models/Watermelon/watermelon.gltf");

	m_spgoaltex = std::make_shared<KdTexture>();
	m_spgoaltex->Load("Asset/Textures/Goal/goal.png");

	m_spbluetex = std::make_shared<KdTexture>();
	m_spbluetex->Load("Asset/Textures/lightblue.png");

	m_bluealphaAdd = -0.015f;//alpha値を増やすか減らすか
	m_bluealpha = 1.0f;		//blueの透明度
	m_bblue = true;			//blueの画像を出すか

	m_pos = { 0,0,50 };

	Math::Matrix _scaleMat;
	_scaleMat = Math::Matrix::CreateScale(10.0f);
	Math::Matrix _transMat;

	_transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = _scaleMat * _transMat;

	//ゴールをしたか
	m_isgoal = false;

	//ゴール文字画像の透明度
	m_alpha = 0.0f;

	m_isReturn = true;
	m_isnextScene = false;


	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("Ground", m_spModel, KdCollider::TypeGround);
}

void Goal::Update()
{

	Math::Vector3 _player;
	_player = m_wpplayer.lock()->GetPos();

	Math::Vector3 _dist;
	_dist = m_pos - _player;

	if (_dist.Length() < 3.0f)
	{
		if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
		{
			//if(!m_isgoal)m_seSuika=KdAudioManager::Instance().Play("Asset/Sounds/SE/suika-wareru.wav", false);

			m_isgoal = true;

			
		}

		/*if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
		{
			if (!m_isReturn)
			{
				m_isReturn = true;
				if (m_alpha >= 1.0f)
				{
					if (!m_bblue)
					{
						m_bblue = true;
						m_bluealphaAdd *= -1;
					}
				}
			}
		}
		else
		{
			m_isReturn = false;
		}*/
		
	}

	//ゴールしたら文字画像の透明度を上げる
	if (m_isgoal)
	{
		if (!m_issegoal)
		{
			m_issegoal = true;
			m_seSuika = KdAudioManager::Instance().Play("Asset/Sounds/SE/suika-wareru.wav", false);
			m_seSuika.lock()->SetVolume(0.5f);

			m_segoal = KdAudioManager::Instance().Play("Asset/Sounds/SE/go-ru.wav", false);


			KdEffekseerManager::GetInstance().Play("sord.efkefc", { 0,3,50 }, 2.0f, 0.8f, false);
			m_seexplosion = KdAudioManager::Instance().Play("Asset/Sounds/SE/explosion.wav", false);


			m_segoal.lock()->SetVolume(0.5f);
			if (m_segoal.expired() == false)
			{
				//m_segoal.lock()->SetVolume(m_goalvol);
			}
		}

		m_alpha += 0.01f;
		if (m_wptime.expired() == false)
		{
			m_wptime.lock()->SetGoal(true);
		}

		if (m_alpha > 1.0f)
		{
			m_alpha = 1.0f;

			
			m_bluealphaAdd =0.015f;

			m_bblue = true;
		}

		//if(m_segoal.lock()->IsStopped())
	}

	

	//青画像の透明度を変える
	if (m_bblue)
	{
		m_bluealpha += m_bluealphaAdd;

		if (m_bluealphaAdd < -0.01f)
		{
			if (m_bluealpha < 0.0f)
			{
				m_bluealpha = 0.0f;
				m_bblue = false;
			}
		}

		if (m_bluealpha > 1.1f)
		{
			m_bluealpha = 1.1f;
			m_bblue = false;
			m_isnextScene = true;
		}

	}

	if (m_isnextScene)
	{
		KdAudioManager::Instance().StopAllSound();

		if (m_wptime.expired() == false)
		{
			int _onetime = m_wptime.lock()->GetOneTime();
			int _tentime = m_wptime.lock()->GetTenTime();
			int _hundredtime = m_wptime.lock()->GetHundredTime();
			int _thousandtime = m_wptime.lock()->GetThousandTime();

			SceneManager::Instance().RetentionTime(_onetime, _tentime, _hundredtime,_thousandtime);
		}

		SceneManager::Instance().SetNextScene
		(
			SceneManager::SceneType::Result
		);
	}

	
}

void Goal::DrawLit()
{
	//スイカ
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);

}

void Goal::DrawSprite()
{
	if (m_isgoal)
	{
		//ゴール文字画像
		Math::Color goalcolor = { 1.0f,1.0f,1.0f,m_alpha };
		Math::Rectangle goalrc = { 0,0,(long)m_spgoaltex->GetWidth(),(long)m_spgoaltex->GetHeight() };
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_spgoaltex, 0, 100, goalrc.width, goalrc.height, &goalrc, &goalcolor);
	}

	//青画像
	Math::Color bluecolor = { 1.0f,1.0f,1.0f,m_bluealpha };
	Math::Rectangle bluerc = { 0,0,(long)m_spbluetex->GetWidth(),(long)m_spbluetex->GetHeight() };
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_spbluetex, 0, 0, bluerc.width, bluerc.height, &bluerc, &bluecolor);

}
