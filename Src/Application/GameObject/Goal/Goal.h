#pragma once

class Character;
class Time;

class Goal : public KdGameObject
{
public:
	Goal(){}
	~Goal()override{}

	void Init()override;
	void Update()override;
	void DrawLit()override;
	void DrawSprite()override;

	Math::Vector3 GetPos() { return m_pos; }
	bool GetGoal() { return m_isgoal; }

	void SetPlayer(std::shared_ptr<Character> _player)
	{
		m_wpplayer = _player;
	}

	void SetTime(std::shared_ptr<Time> _time)
	{
		m_wptime = _time;
	}

private:
	std::shared_ptr<KdModelData> m_spModel;
	std::shared_ptr<KdTexture> m_spgoaltex;

	//シーン遷移時の青画像
	std::shared_ptr<KdTexture> m_spbluetex;

	std::weak_ptr<Character> m_wpplayer;
	std::weak_ptr<Time> m_wptime;

	Math::Vector3 m_pos;

	bool m_isgoal;

	float m_alpha;

	float m_bluealphaAdd;		//alpha値を増やすか減らすか
	float m_bluealpha;			//青画像の透明度
	bool m_bblue;				//青画像を出すか

	bool m_isReturn;			//リターンキー制御
	bool m_isnextScene;			//次のシーンへ行くか

	//音のインスタンスを保存
	std::weak_ptr<KdSoundInstance> m_seSuika;		//波の音
	std::weak_ptr<KdSoundInstance> m_segoal;		//波の音
	float m_goalvol = 0.2f;						//音量
	bool m_issegoal = false;							//音を下げるか

	std::weak_ptr<KdSoundInstance> m_seexplosion;


};

