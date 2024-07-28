#include "TitleCamera.h"

void TitleCamera::Init()
{
	// 親クラスの初期化呼び出し
	CameraBase::Init();

	// 注視点
	m_mLocalPos = Math::Matrix::CreateTranslation(-10.f, 10.f, -3.0f);

	SetCursorPos(m_FixMousePos.x, m_FixMousePos.y);

	m_mRotation = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(350));
	Math::Matrix _rotXMat = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(35));
	Math::Matrix _rotYMat = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(280));

	m_mWorld = _rotXMat * m_mLocalPos * m_mRotation * _rotYMat;
	//m_mWorld = m_mRotation * _rotYMat * m_mLocalPos;

}

void TitleCamera::PostUpdate()
{

}
