#include "DxLib.h"
#include "Player.h"
#include "Light.h"

// �萔
namespace
{
	/*�X�|�b�g���C�g*/
	constexpr float kSpotLightOutAngle = 27.0f;	 // �X�|�b�g���C�g�̉e���p�x
	constexpr float kSpotLightInAngle = 18.0f;	 // �X�|�b�g���C�g�̉e�����������n�߂�p�x
	constexpr float kSpotLightRange = 147.0f;	 // �L������
	constexpr float kSpotLighAtten0 = 0.6f;		 // ���������p�����[�^0
	constexpr float kSpotLighAtten1 = 0.0f;		 // ���������p�����[�^1
	constexpr float kSpotLighAtten2 = 0.0f;		 // ���������p�����[�^2
	constexpr float kSpotLightDistance = 10.0f;  // ���C�g�ƃv���C���[�̋���
	const VECTOR kSpotLightPos = VGet(-50.0f, -20.0f, -116.0f); // �X�|�b�g���C�g�ʒu
	const VECTOR kSpotLightDir = VGet(1.0f, 0.43f, 1.0f);		// �X�|�b�g���C�g����
}


/// <summary>
/// ���C�g�쐬
/// </summary>
void Light::Create(std::shared_ptr<Player> pPlayer)
{
	m_pPlayer = pPlayer;
	//m_dirLight = CreateDirLightHandle(VGet(0, 0, 0));

	m_spotLight = CreateSpotLightHandle(kSpotLightPos, kSpotLightDir, kSpotLightOutAngle, kSpotLightInAngle,
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
	const VECTOR cameraPos = GetCameraPosition();  // �J�����ʒu�擾
	const VECTOR playerPos = m_pPlayer->GetPos();  // �v���C���[�ʒu�擾
	VECTOR cameraToPlayerDir = VNorm(VSub(playerPos, cameraPos)); // �J��������v���C���[�܂ł̃x�N�g�����v�Z����

	//SetLightDirectionHandle(m_dirLight, cameraToPlayerDir);
	SetLightPosition(VAdd(playerPos, kSpotLightPos));
}


#ifdef _DEBUG
/// <summary>
/// �`��
/// </summary>
void Light::Draw()
{
	DrawFormatString(0, 200, 0xffffff, "���C�g�ʒu(X:%.2f,Y:%.2f,Z;%.2f)", GetLightPositionHandle(m_spotLight).x, GetLightPositionHandle(m_spotLight).y, GetLightPositionHandle(m_spotLight).z);
	DrawFormatString(0, 220, 0xffffff, "���C�g����(X:%.2f,Y:%.2f,Z;%.2f)", GetLightDirectionHandle(m_spotLight).x, GetLightDirectionHandle(m_spotLight).y, GetLightDirectionHandle(m_spotLight).z);
}
#endif

