#pragma once

class Result :public KdGameObject
{
public:
	Result() {}
	~Result() override {}

	void Init()override;
	void Update()override;
	void DrawSprite()override;
	void DrawLit()override;
	
	void OneTime();
	void TenTime();
	void HundredTime();
	void ThousandTime();

private:
	
	//小さいスイカ
	std::shared_ptr<KdModelData> m_spWatermellonModel;

	//リザルト文字画像
	std::shared_ptr<KdTexture> m_sptex;

	//シーン遷移時の青画像
	std::shared_ptr<KdTexture> m_spbluetex;

	float m_bluealphaAdd;		//alpha値を増やすか減らすか
	float m_bluealpha;			//青画像の透明度
	bool m_bblue;				//青画像を出すか

	bool m_isReturn;			//リターンキー制御
	bool m_isnextScene;			//次のシーンへ行くか




	//================================================================
	//タイム
	std::shared_ptr<KdTexture> m_pzero = nullptr;	//0
	std::shared_ptr<KdTexture> m_pone = nullptr;	//1
	std::shared_ptr<KdTexture> m_ptwo = nullptr;	//2
	std::shared_ptr<KdTexture> m_pthree = nullptr;	//3
	std::shared_ptr<KdTexture> m_pfour = nullptr;	//4
	std::shared_ptr<KdTexture> m_pfive = nullptr;	//5
	std::shared_ptr<KdTexture> m_psix = nullptr;	//6
	std::shared_ptr<KdTexture> m_pseven = nullptr;	//7
	std::shared_ptr<KdTexture> m_peight = nullptr;	//8
	std::shared_ptr<KdTexture> m_pnine = nullptr;	//9
	std::shared_ptr<KdTexture> m_pcoron = nullptr;	//:

	std::shared_ptr<KdTexture> m_prank = nullptr;	//ランク文字
	std::shared_ptr<KdTexture> m_pSrank = nullptr;	//S文字
	std::shared_ptr<KdTexture> m_pArank = nullptr;	//A文字
	std::shared_ptr<KdTexture> m_pBrank = nullptr;	//B文字
	std::shared_ptr<KdTexture> m_pCrank = nullptr;	//C文字

	int m_onetime = 0;				//1の位
	int m_tentime = 0;				//10の位
	int m_hundredtime = 0;			//100の位
	int m_thousandtime = 0;			//1000の位


	float m_resultalphaAdd;		//alpha値を増やすか減らすか
	float m_resultalpha;			//青画像の透明度
	//bool m_bresult;				//青画像を出すか

	float m_rankalphaAdd;		//alpha値を増やすか減らすか
	float m_rankalpha;			//青画像の透明度

};

