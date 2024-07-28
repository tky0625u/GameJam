#pragma once

class Time :public KdGameObject
{
public:

	Time(){}
	~Time()override{}

	void Init()override;
	void Update()override;
	void DrawSprite()override;

	void OneTime();
	void TenTime();
	void HundredTime();
	void ThousandTime();

	const int GetOneTime() const { return m_onetime; }
	const int GetTenTime() const { return m_tentime; }
	const int GetHundredTime() const { return m_hundredtime; }
	const int GetThousandTime() const { return m_thousandtime; }

	void SetStart(bool _start) { m_isstart = _start; }
	void SetGoal(bool _goal) { m_isgoal = _goal; }

private:

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

	int m_time;					//スコア
	int m_onetime;				//1の位
	int m_tentime;				//10の位
	int m_hundredtime;			//100の位
	int m_thousandtime;			//1000の位

	bool m_isstart;				//カウントダウンが終わるまでは進めない
	bool m_isgoal;				//ゴールしたら止める


};

