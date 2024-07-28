#pragma once

class Character;
class Goal;

class Distance :public KdGameObject
{
public:
	Distance() {}
	~Distance() override{}

	void Init()override;
	void Update()override;
	void DrawSprite()override;

	void SetPlayer(std::shared_ptr<Character> _player)
	{
		m_wpplayer = _player;
	}

	void SetGoal(std::shared_ptr<Goal> _goal)
	{
		m_wpgoal = _goal;
	}

private:
	std::shared_ptr<KdTexture> m_pstarttex;
	std::shared_ptr<KdTexture> m_pgoaltex;
	std::shared_ptr<KdTexture> m_prodtex;
	std::shared_ptr<KdTexture> m_pcircletex;

	Math::Vector2 m_pos;

	std::weak_ptr<Character> m_wpplayer;
	std::weak_ptr<Goal> m_wpgoal;

	float m_goaldistance;		//開始座標とゴール座標の距離
	float m_playerdistance;		//プレイヤーとゴールの距離
	float m_ratio;				//m_playerdistance/m_goaldistanceの結果を保存

	float m_move;

};

