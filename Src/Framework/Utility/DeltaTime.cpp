#include"DeltaTime.h"

#include <chrono>

void DeltaTime::Init()
{
	DWORD nowTime=timeGetTime();      // 計測スタート時刻を保存

	m_delta.startTime = nowTime;
	m_delta.elapsedTime = 0;
	m_delta.deltaTime = 0;

	m_oldTime = nowTime;
}

void DeltaTime::Update()
{
	DWORD nowTime;
	nowTime = timeGetTime(); //現在時刻を取得

	m_delta.elapsedTime = nowTime - m_delta.startTime;
	m_delta.deltaTime = nowTime - m_oldTime;
	m_oldTime = nowTime;

	if (m_slowFlg)
	{
		Slow();
	}
}

double DeltaTime::GetTimeDif(double a_newTime, double a_oldTime)
{
	double _timeDif = 0.0;

	//差を計算
	_timeDif = a_newTime - a_oldTime;

	///0より小さかったら0にする
	if (_timeDif < 0.0)_timeDif = 0.0;

	//現実時間で返す
	_timeDif /= 1000.0;

	return _timeDif;
}


void DeltaTime::Slow()
{

	m_slow.elapsedTime = timeGetTime();
	if ((m_slow.elapsedTime - m_slow.startTime) / 1000.0f > m_slowTime)
	{
		m_slowFlg = false;
		m_slowInter = 1.0;
	}


}