#pragma once
//============================================================
// アプリケーションの時間制御 
//============================================================
struct S_DeltaTime
{
	double startTime = 0.0;           //計測開始した時点での秒数[秒]
	double elapsedTime=0.0;         //経過時間[秒]
	double deltaTime=0.0;           //前フレームからの経過時間[秒]
};

class DeltaTime
{
public:

	void Init();
	void Update();

	//二つの時間の差を現実の時間で返す
	double GetTimeDif(double a_newTime, double a_oldTime);

	//前回からの経過フレームを返す
	double GetDeltaTime() { return (m_delta.deltaTime / m_slowInter) / 1000.0f; }
	double GetDefDeltaTime() { return m_delta.deltaTime / 1000.0f; }

	//現在の減速率を取得
	float GetSlowInter() { return m_slowInter; }

	//減速セット
	void SetSlow(float a_slowInter, double a_slowTime) {
		m_slowFlg = true;
		m_slowInter = a_slowInter;

		//0にならないように
		if (m_slowInter <= 0) { m_slowInter = 0.01f; }

		m_slowTime = a_slowTime;
		m_slow.startTime = timeGetTime();
	}

	//gui用、速度セット
	void SetSlow(float a_slowInter)
	{
		m_slowInter = a_slowInter;

		//0にならないように
		if (m_slowInter <= 0) { m_slowInter = 0.01f; }
	}

private:
	void Release() {}


	//前回時刻
	DWORD m_oldTime=0;

	S_DeltaTime m_delta = {};

	//減速処理
	bool m_slowFlg = false;
	float m_slowInter = 1;
	double m_slowTime = 0;
	S_DeltaTime m_slow = {};
	void Slow();



//=====================================================
// シングルトンパターン
//=====================================================
private:

	DeltaTime() {}
	~DeltaTime() { Release(); }

public:
	static DeltaTime& Instance() {
		static DeltaTime Instance;
		return Instance;
	}
};

