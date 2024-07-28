#pragma once
class Enemy5 : public KdGameObject
{
public:
	Enemy5() {}
	~Enemy5()			override {}

	void Init()				override;
	void Update()			override;
	void PostUpdate()		override;
	void DrawLit()			override;

	void SetTarget(std::shared_ptr<KdGameObject> _wpTarget)
	{
		m_wpTarget = _wpTarget;
	}

private:

	void UpdateRotate(const Math::Vector3& srcMoveVec);

	std::shared_ptr<KdModelWork>		m_spModel = nullptr;
	std::shared_ptr<KdAnimator>			m_spAnimater = nullptr;
	std::weak_ptr<KdGameObject> m_wpTarget;

	Math::Vector3 m_pos;
	Math::Vector3 m_worldRot;
	Math::Vector3 m_dir;
	float m_Speed = 0.05f;
	float m_Ani_Speed = 0.f;

	bool m_isFlg = false;
};