#pragma once
class Enemy6 : public KdGameObject
{
public:
	Enemy6() {}
	~Enemy6()			override {}

	void Init()				override;
	void Update()			override;
	void PostUpdate()		override;
	void DrawLit()			override;

	void SetTarget(std::shared_ptr<KdGameObject> _wpTarget)
	{
		m_wpTarget = _wpTarget;
	}

	void SetPos(const Math::Vector3& pos)override { m_pos=pos; }

	void SetDir(Math::Vector3 a_dir) { m_dir = a_dir; }

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
	int angle = 0;
	bool m_isFlg = false;

	float m_anglePlus = 0;

	bool isflg = 0;
	
	int cnt = 1;

	//移動する間隔
	float m_moveRad = 1.0f;


};