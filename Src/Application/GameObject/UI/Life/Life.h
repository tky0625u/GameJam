#pragma once

class Life :public KdGameObject
{
public:
	Life(){}
	~Life()override{}

	void Init()override;
	void Update()override;
	void DrawSprite()override;

	void SetPos(Math::Vector2 _pos) { m_pos = _pos; }
	void OnHit()override;

private:
	std::shared_ptr<KdTexture> m_ptex;
	Math::Vector2 m_pos;

};
