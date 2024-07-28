#pragma once
#include"../BaseGui.h"


class ObjectGui:public BaseGui
{
public:
	ObjectGui(std::string_view a_name) :BaseGui(a_name) { Init(); }
	~ObjectGui() {}

	void Init()override;
	void ChildUpdate()override;

private:

	//保存用
	std::string m_inputName = "0";
	Math::Vector3 m_inputPos = {};

	bool m_addFlg = false;

};
