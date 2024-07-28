#pragma once

#include"../BaseScene/BaseScene.h"

class GameScene : public BaseScene
{
public :

	GameScene()		{}
	~GameScene()	{}

private:
	void RegistObj();

	void Event() override;
	void Init() override;

	void Load(std::string _filePath);

	// 乱数生成器
	std::shared_ptr<KdRandomGenerator> m_RandomGen;


	//音のインスタンスを保存
	std::weak_ptr<KdSoundInstance> m_sewave;		//波の音

	std::weak_ptr<KdSoundInstance> m_segaya;		//ガヤガヤ音
};
