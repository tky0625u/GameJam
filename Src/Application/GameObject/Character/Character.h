#pragma once

class P_ActionManager;

class CameraBase;
class Character : public KdGameObject, public std::enable_shared_from_this<Character>
{
public:
	Character()							{}
	~Character()			override	{}

	void Init()				override;
	void Update()			override;
	void PostUpdate()		override;

	void DrawLit()			override;
	void DrawUnLit()		override;

	void SetCamera(const std::shared_ptr<CameraBase>& camera)
	{
		m_wpCamera = camera;
	}

	void UpdateRotate(const Math::Vector3& srcMoveVec);

	//animationをセットする
	void SetAnimation(std::string_view a_name, bool a_isLoop) { m_spAnimater->SetAnimation(m_spModel->GetData()->GetAnimation(a_name), a_isLoop); m_animSpeed = 1.0f; }
	void SetAnimation(std::string_view a_name, bool a_isLoop, float a_animSpeed) { m_spAnimater->SetAnimation(m_spModel->GetData()->GetAnimation(a_name), a_isLoop); m_animSpeed = a_animSpeed; }

	//animationが終わっているか
	bool IsAnimEnd() { return  m_spAnimater->IsAnimationEnd(); }

	//ボーンを返す
	Math::Matrix GetWeaponMat(){
		return m_spModel->FindWorkNode("ik_hand_gun")->m_localTransform* m_spModel->FindWorkNode("ik_hand_root")->m_worldTransform*(Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_worldRot.y))*Math::Matrix::CreateTranslation(m_mWorld.Translation()));
	}

	void SetStart(bool a_start) { m_start = a_start; }
	bool GetStart() { return m_start; }

	void OnHit()override;

private:

	bool m_start = false;

	std::shared_ptr<KdModelWork>		m_spModel		= nullptr;
	std::shared_ptr<KdAnimator>			m_spAnimater	= nullptr;
	std::weak_ptr<CameraBase>			m_wpCamera;

	Math::Vector3						m_worldRot;

	float m_animSpeed = 0.0f;

	//行動管理クラス
	std::shared_ptr<P_ActionManager> m_actionManager = nullptr;



	//=======================================================================================
	bool m_isEffekseer;			//エフェクシア制御

	int m_life=3;					//HP

	bool m_ismuteki=false;			//無敵にする
	int m_mutekiframe=0;			//無敵時間

	float m_alpha=1.0f;		//スペース画像の透明度を変える
	float m_alphaAdd;	//スペース画像の透明度の増減値

	bool m_isdeath = false;;		//死亡したか
	int m_deathframe;	//死亡後何秒後にリセットするか

	bool m_moveFLg = true;
	bool m_keyFlg = false;

	bool m_hitFlg = false;
};