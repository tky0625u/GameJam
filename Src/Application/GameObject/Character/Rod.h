#pragma once

class Character;

class Rod : public KdGameObject
{
public:
	Rod() {}
	virtual ~Rod()		override {}

	void Init()				override;
	void Update()			override;
	void DrawLit()			override;

	void SetTarget(std::shared_ptr<Character> a_mat) { m_target = a_mat; }

private:
	std::shared_ptr<KdModelWork> m_spModel = nullptr;

	std::weak_ptr<Character> m_target;
};