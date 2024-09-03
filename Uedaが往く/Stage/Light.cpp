#include "Light.h"

// �萔
namespace
{
	/*�X�|�b�g���C�g*/
	constexpr float kSpotLightOutAngle = 0.0f;					 // �X�|�b�g���C�g�R�[���̊O���̊p�x
	constexpr float kSpotLightInAngle = 90.0f;					 // �X�|�b�g���C�g�R�[���̓����̊p�x
	constexpr float kSpotLightRange = 100.0f;					 // �L������
	constexpr float kSpotLighAtten0 = 0.0f;						 // ���������p�����[�^0
	constexpr float kSpotLighAtten1 = 0.001f;					 // ���������p�����[�^1
	constexpr float kSpotLighAtten2 = 0.0f;						 // ���������p�����[�^2
}


/// <summary>
/// ���C�g�쐬
/// </summary>
void Light::Create()
{
	// �X�|�b�g���C�g�쐬
	m_spotLight = CreateSpotLightHandle(GetCameraPosition(), GetCameraTarget(), kSpotLightOutAngle, kSpotLightInAngle,
		kSpotLightRange, kSpotLighAtten0, kSpotLighAtten1, kSpotLighAtten2);
}


/// <summary>
/// ���C�g�폜
/// </summary>
void Light::Delete()
{
	DeleteLightHandleAll();
}


/// <summary>
/// ���C�g�X�V
/// </summary>
void Light::Update()
{
	SetLightPositionHandle(m_spotLight, GetCameraPosition());
}
