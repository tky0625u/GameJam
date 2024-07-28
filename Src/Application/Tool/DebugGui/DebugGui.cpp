#include "DebugGui.h"

#include"Application/main.h"

void DebugGui::Init()
{
	


}

void DebugGui::Update()
{
	ImGui::SetNextWindowPos(ImVec2(300, 20), 2);
	ImGui::SetNextWindowSize(ImVec2(200, 150), 2);

	// デバッグウィンドウ
	if (ImGui::Begin("DebugGui"))
	{
		// FPS
		ImGui::Text("FPS : %d", Application::Instance().GetNowFPS());

		//fps変更
		ImGui::SliderInt("FPS_Trans", &m_maxFps, 20, 120);

		//時間の流れ
		ImGui::Checkbox("gameSpeed_Flg", &m_gameSpeedFlg);
		ImGui::SliderFloat("GameSpeed_Trans", &m_gameSpeed, 0.1f, 5.0f);

		//デバッグスフィア
		ImGui::Checkbox("debugSphere_Flg", &m_debugSphere);
	}
	ImGui::End();



	//ゲームスピードの変化
	if (m_gameSpeedFlg)
	{
		DeltaTime::Instance().SetSlow(m_gameSpeed);
	}
}
