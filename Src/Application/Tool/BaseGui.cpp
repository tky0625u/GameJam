#include "BaseGui.h"

#include"GuiManager.h"

void BaseGui::Init()
{
	
}

void BaseGui::Update()
{
	ImGui::SetNextWindowPos(ImVec2(450+(GuiManager::Instance().GetGuiListSize()*100), 20), 2);
	ImGui::SetNextWindowSize(ImVec2(200, 150), 2);

	// デバッグウィンドウ
	if (ImGui::Begin(m_name.data()))
	{
		//継承した更新
		ChildUpdate();

		for (auto& dataList : m_dataList)
		{
			//ツリー構造にする
			int flags = ImGuiTreeNodeFlags_NoAutoOpenOnLog | ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick;
			bool bTreeOpen = false;

			ImGui::PushID(dataList.first.data());

			bTreeOpen = ImGui::TreeNodeEx((void*)1, flags, dataList.first.data());

			if(bTreeOpen)
			{
				

				//配列部分を読む
				for (auto& guiData : dataList.second)
				{
					if (guiData.m_data.type() == typeid(bool*))
					{
						ImGui::Checkbox(guiData.m_name.data(), std::any_cast<bool*>(guiData.m_data));
					}
					//文字のみ
					else if (guiData.m_data.type() == typeid(std::string_view))
					{
						ImGui::Text(std::any_cast<std::string_view>(guiData.m_data).data());
					}
					//スライダー(float)
					else if (guiData.m_data.type() == typeid(SliderFloatInfo))
					{
						float* _data = std::any_cast<SliderFloatInfo>(guiData.m_data).m_data;
						float _min = std::any_cast<SliderFloatInfo>(guiData.m_data).m_min;
						float _max = std::any_cast<SliderFloatInfo>(guiData.m_data).m_max;

						ImGui::SliderFloat(guiData.m_name.data(), _data, _max, _min);
					}
					//スライダー(int)
					else if (guiData.m_data.type() == typeid(SliderIntInfo))
					{
						int* _data = std::any_cast<SliderIntInfo>(guiData.m_data).m_data;
						int _min = std::any_cast<SliderIntInfo>(guiData.m_data).m_min;
						int _max = std::any_cast<SliderIntInfo>(guiData.m_data).m_max;

						ImGui::SliderInt(guiData.m_name.data(), _data, _max, _min);
					}
					//ドラッグ(float)
					else if (guiData.m_data.type() == typeid(DragFloatInfo))
					{
						float* _data = std::any_cast<DragFloatInfo>(guiData.m_data).m_data;
						float _col = std::any_cast<DragFloatInfo>(guiData.m_data).m_col;

						ImGui::DragFloat(guiData.m_name.data(), _data,_col);
					}
				}

				ImGui::TreePop();
			}

			ImGui::PopID();
		}
	}
	ImGui::End();
}
