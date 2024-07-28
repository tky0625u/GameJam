#pragma once
class Enemy1 : public KdGameObject
{
public:
	Enemy1() {}
	~Enemy1()			override {}

	void Init()				override;
	void Update()			override;
	
	void DrawLit()			override;


private:

	std::shared_ptr<KdModelData> m_model;

	

};