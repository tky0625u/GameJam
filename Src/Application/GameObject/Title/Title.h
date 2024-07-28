#pragma once

class Title :public KdGameObject
{
public:
	Title(){}
	~Title()override{}

	void Init()override;
	void Update()override;
	void DrawSprite()override;


private:
	std::shared_ptr<KdTexture> m_sptex;
	//エンター文字画像
	std::shared_ptr<KdTexture> m_spentertex;

	//シーン遷移時の青画像
	std::shared_ptr<KdTexture> m_spbluetex;

	//音のインスタンスを保存
	std::weak_ptr<KdSoundInstance> m_sewave;		//波の音
	float m_wavevol = 0.5f;						//音量
	bool m_iswave = false;							//音を下げるか

	//音のインスタンスを保存
	std::weak_ptr<KdSoundInstance> m_sestart;		//開始音

	float m_enteralphaAdd;
	float m_enteralpha;

	float m_bluealphaAdd;		//alpha値を増やすか減らすか
	float m_bluealpha;			//青画像の透明度
	bool m_bblue;				//青画像を出すか

	bool m_isReturn;			//リターンキー制御
	bool m_isnextScene;			//次のシーンへ行くか

};

