#include "Distance.h"
#include"../../Goal/Goal.h"
#include"../../Character/Character.h"

void Distance::Init()
{
	m_pstarttex = std::make_shared<KdTexture>();
	m_pstarttex->Load("Asset/Textures/UI/start.png");

	m_pgoaltex = std::make_shared<KdTexture>();
	m_pgoaltex->Load("Asset/Textures/UI/goal.png");

	m_prodtex = std::make_shared<KdTexture>();
	m_prodtex->Load("Asset/Textures/UI/square.png");

	m_pcircletex = std::make_shared<KdTexture>();
	m_pcircletex->Load("Asset/Textures/UI/circle.png");

	m_pos = { 500,-200 };

	m_goaldistance = 0.0f;
	m_playerdistance = 0.0f;

	m_ratio = 0.0f;
	


	m_move = 0;
}

void Distance::Update()
{

	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		m_move += 0.3f;
		if (m_move > 300)
		{
			m_move = 300;
		}
	}

	if (m_wpgoal.lock()->GetGoal())return;

	//プレイヤー座標
	Math::Vector3 _player;
	_player=m_wpplayer.lock()->GetPos();
	//_player = { 0,0,m_move };

	//開始座標
	Math::Vector3 _start;
	_start = {};

	//ゴール座標
	Math::Vector3 _goal;
	_goal = m_wpgoal.lock()->GetPos();

	//スタート位置とゴールの距離
	Math::Vector3 _goaldistance;
	_goaldistance = _goal - _start;

	//現在のプレイヤーの位置とゴールの距離
	Math::Vector3 _playerdistance;
	_playerdistance = _goal - _player;

	//スタート位置とゴールの距離を取る
	m_goaldistance = _goaldistance.Length();

	//現在のプレイヤー座標とゴールの距離を取る
	m_playerdistance = _playerdistance.Length();

	//何割進んだかを求める
	m_ratio = 1.0f - m_playerdistance / m_goaldistance;
	
	m_pos.y = -200.0f + 450.0f * m_ratio;

	if (m_pos.y > 250)
	{
		m_pos.y = 250;
	}

}

void Distance::DrawSprite()
{
	//スタートとゴールの距離を示す棒
	Math::Color rodcolor = { 1.0f,1.0f,1.0f,0.5f };
	Math::Rectangle rodrc = { 0,0,(long)m_prodtex->GetWidth(),(long)m_prodtex->GetHeight()};
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_prodtex, 500, 25, rodrc.width, rodrc.height * 1.5f, &rodrc, &rodcolor);

	//スタート画像
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_pstarttex, 500, -200);

	//ゴール画像
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_pgoaltex, 500, 250);

	//プレイヤーの位置を示す画像
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_pcircletex, m_pos.x, m_pos.y);

}
