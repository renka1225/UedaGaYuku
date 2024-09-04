#include "DxLib.h"
#include "Player.h"
#include "Light.h"

// �萔
namespace
{
	/*�X�|�b�g���C�g*/
	constexpr float kSpotLightOutAngle = 45.0f;	 // �X�|�b�g���C�g�̉e���p�x
	constexpr float kSpotLightInAngle = 30.0f;	 // �X�|�b�g���C�g�̉e�����������n�߂�p�x
	constexpr float kSpotLightRange = 200.0f;	 // �L������
	constexpr float kSpotLighAtten0 = 0.0f;		 // ���������p�����[�^0
	constexpr float kSpotLighAtten1 = 0.015f;	 // ���������p�����[�^1
	constexpr float kSpotLighAtten2 = 0.0f;		 // ���������p�����[�^2
	//const VECTOR kSpotLightPos = VGet(-40.0f, 0.0f, -45.0f); // ���C�g�ʒu
	constexpr float kSpotLightDistance = 10.0f;  // ���C�g�ƃv���C���[�̋���
}


/// <summary>
/// ���C�g�쐬
/// </summary>
void Light::Create(std::shared_ptr<Player> pPlayer)
{
	m_pPlayer = pPlayer;
	const VECTOR cameraPos = GetCameraPosition();  // �J�����ʒu�擾
	const VECTOR cameraTarget = GetCameraTarget(); // �J���������擾
	const VECTOR playerPos = m_pPlayer->GetPos();  // �v���C���[�ʒu�擾
	const VECTOR playerDir = m_pPlayer->GetDir();  // �v���C���[�̕����擾
	VECTOR cameraToPlayerDir = VNorm(VSub(playerPos, cameraPos)); // �J��������v���C���[�܂ł̃x�N�g�����v�Z����

	// �X�|�b�g���C�g�쐬
	//m_spotLight = CreateSpotLightHandle(cameraPos, VAdd(playerPos, cameraToPlayerDir), kSpotLightOutAngle, kSpotLightInAngle,
		//kSpotLightRange, kSpotLighAtten0, kSpotLighAtten1, kSpotLighAtten2);

	m_spotLight = CreateSpotLightHandle(VAdd(playerPos, VScale(playerDir, kSpotLightDistance)), playerPos, kSpotLightOutAngle, kSpotLightInAngle,
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
	//const VECTOR cameraPos = GetCameraPosition();  // �J�����ʒu�擾
	//const VECTOR playerPos = m_pPlayer->GetPos();  // �v���C���[�ʒu�擾
	//VECTOR cameraToPlayerDir = VNorm(VSub(playerPos, cameraPos)); // �J��������v���C���[�܂ł̃x�N�g�����v�Z����

	//SetLightPositionHandle(m_spotLight, VAdd(playerPos, kSpotLightPos));

	const VECTOR playerPos = m_pPlayer->GetPos();   // �v���C���[�ʒu�擾
	const VECTOR playerDir = m_pPlayer->GetDir();  // �v���C���[�̌����擾

	// ���C�g���v���C���[�̐��ʂɔz�u
	VECTOR lightPos = VAdd(playerPos, VScale(playerDir, kSpotLightDistance));

	SetLightPositionHandle(m_spotLight, lightPos);
}


#ifdef _DEBUG
/// <summary>
/// �`��
/// </summary>
void Light::Draw()
{
	DrawFormatString(0, 200, 0xffffff, "���C�g�ʒu:(X:%.2f,Y:%.2f,Z;%.2f)", GetLightPositionHandle(m_spotLight).x, GetLightPositionHandle(m_spotLight).y, GetLightPositionHandle(m_spotLight).z);
}
#endif

