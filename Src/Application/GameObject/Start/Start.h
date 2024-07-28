#pragma once

class Time;
class Character;

class Start :public KdGameObject
{
public:
	Start(){}
	~Start()override{}

	void Init()override;
	void Update()override;
	void DrawSprite()override;

	void SetPlayer(std::shared_ptr<Character> _player) { m_wpplayer = _player; }
	void SetTime(std::shared_ptr<Time> _time) { m_wptime = _time; }

private:
	std::shared_ptr<KdTexture> m_sponeTex;
	std::shared_ptr<KdTexture> m_sptwoTex;
	std::shared_ptr<KdTexture> m_spthreeTex;
	std::shared_ptr<KdTexture> m_spstartTex;
	
	//音のインスタンスを保存
	std::weak_ptr<KdSoundInstance> m_secountdown;		//カウントダウン

	std::weak_ptr<Time> m_wptime;

	std::weak_ptr<Character> m_wpplayer;

	int m_countframe = 0;
	int m_count = 0;




};

