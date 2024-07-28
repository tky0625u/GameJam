#pragma once

class Terrain : public KdGameObject
{
public:
	Terrain() {}
	virtual ~Terrain()		override {}

	void SetType(std::shared_ptr<KdModelData> a_spModel);

	void Init()				override;
	void Update()			override;
	void DrawLit()			override;

private:
	std::shared_ptr<KdModelData> m_spModel = nullptr;

};