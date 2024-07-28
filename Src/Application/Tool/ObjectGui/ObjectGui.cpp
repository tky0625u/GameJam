#include "ObjectGui.h"
#include"../../Scene/SceneManager.h"

void ObjectGui::Init()
{

}

void ObjectGui::ChildUpdate()
{
	//オブジェクト追加GUI

	//追加するオブジェクト
	ImGui::InputText("ObjectName", &m_inputName);

	ImGui::InputFloat("Pos.x",&m_inputPos.x, 0.1f);
	ImGui::InputFloat("Pos.y", &m_inputPos.y, 0.1f);
	ImGui::InputFloat("Pos.z", &m_inputPos.z, 0.1f);

	//オブジェクトを追加
	if (ImGui::Button("Add"))
	{
		if (!m_addFlg)
		{
			std::shared_ptr<KdGameObject>_obj = KdGameObjectFactory::Instance().CreateGameObject(m_inputName);

			if (_obj != nullptr)
			{
				std::string _inputName = m_inputName;
				Math::Vector3 _pos = m_inputPos;

				SceneManager::Instance().AddDefObject(_obj, _inputName, _pos);
			}
			else
			{
				//警告音
				MessageBeep(MB_OK);
			}

			m_addFlg = true;
		}
	}
	else
	{
		m_addFlg = false;
	}

	
}
