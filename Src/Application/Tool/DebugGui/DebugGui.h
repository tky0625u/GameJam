#pragma once

class DebugGui
{
public:


	void Init();
	void Update();

	const int GetFps() { return m_maxFps; }
	const bool GetDebugSphere(){ return m_debugSphere; }

private:

	int m_maxFps = 60;

	float m_gameSpeed = 1.0f;
	bool m_gameSpeedFlg = false;


	//デバッグスフィア
	bool m_debugSphere = true;


//=====================================================
// シングルトンパターン
//=====================================================
private:
	DebugGui() {}
	~DebugGui() {}


public:
	static DebugGui& Instance() {
		static DebugGui Instance;
		return Instance;
	}

};
