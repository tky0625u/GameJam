#pragma once
class Enemy2 : public KdGameObject
{
public:
	Enemy2() {}
	~Enemy2()			override {}

	void Init()				override;
	void Update()			override;
	
	void DrawLit()			override;


private:

	std::shared_ptr<KdModelData> m_model;
};