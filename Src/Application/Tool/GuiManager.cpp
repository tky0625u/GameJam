#include "GuiManager.h"
#include"Application/main.h"

#include"BaseGui.h"

void GuiManager::Init()
{
}

void GuiManager::Update()
{

	//guiリスト分回す
	for (auto& list : m_guiList)
	{
		list.second->Update();
	}
}
