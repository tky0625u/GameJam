#pragma once

#include"../BaseScene/BaseScene.h"

class ResultScene : public BaseScene
{
public:

	ResultScene() {  }
	~ResultScene() {}

private:

	void Event() override;
	void Init() override;

	//音のインスタンスを保存
	std::weak_ptr<KdSoundInstance> m_sewave;		//波の音
};
