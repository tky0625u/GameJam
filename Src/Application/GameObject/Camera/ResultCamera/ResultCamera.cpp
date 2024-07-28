#include "ResultCamera.h"

void ResultCamera::Init()
{
	// 親クラスの初期化呼び出し
	CameraBase::Init();

	// 注視点
	//m_mLocalPos = Math::Matrix::CreateTranslation(0.7f, 1.5f, -3.0f);

	/*SetCursorPos(m_FixMousePos.x, m_FixMousePos.y);

	m_mRotation = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(0));
	Math::Matrix _rotYMat = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(30));*/

	m_mLocalPos = Math::Matrix::CreateTranslation(-4.f, 4.f, 5.0f);

	SetCursorPos(m_FixMousePos.x, m_FixMousePos.y);

	//m_mRotation = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(350));
	Math::Matrix _rotXMat = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(25));
	Math::Matrix _rotYMat = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(280));

	m_mWorld = _rotXMat * m_mLocalPos * m_mRotation * _rotYMat;
}

void ResultCamera::PostUpdate()
{
}
