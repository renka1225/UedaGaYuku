#pragma once
#include "DxLib.h"
#include "Input.h"

// �萔
namespace
{
	/*�f�B���N�V���i�����C�g*/
	//const VECTOR kDirLightPos = VGet(4000.0f, 10000.0f, 4000.0f); // �ʒu
	const VECTOR kDirLightPos = VGet(0.0f, 100.0f, 1000.0f);		 // �ʒu
	const VECTOR kDirLightDir = VGet(-1.0f, -1.0f, 1.0f);			 // ����

	/*�|�C���g���C�g*/
	const VECTOR kPointLightPos = VGet(8000.0f, 200.0f, 0.0f);   // �ʒu
	constexpr float kPointLightRange = 1000.0f;					 // �L������
	constexpr float kPointLightAtten0 = 0.0f;					 // ���������p�����[�^0
	constexpr float kPointLightAtten1 = 0.002f;					 // ���������p�����[�^1
	constexpr float kPointLightAtten2 = 0.0f;					 // ���������p�����[�^2

	/*�X�|�b�g���C�g*/
	const VECTOR kSpotLightPos = VGet(8000.0f, 1000.0f, 0.0f);	 // �ʒu
	const VECTOR kSpotLightDir = VGet(-1.0f, -1.0f, 0.0f);		 // ����
	constexpr float kSpotLightOutAngle = 0.0f;					 // �X�|�b�g���C�g�R�[���̊O���̊p�x
	constexpr float kSpotLightInAngle = 180.0f;					 // �X�|�b�g���C�g�R�[���̓����̊p�x
	constexpr float kSpotLightRange = 1000.0f;					 // �L������
	constexpr float kSpotLighAtten0 = 0.0f;						 // ���������p�����[�^0
	constexpr float kSpotLighAtten1 = 0.001f;					 // ���������p�����[�^1
	constexpr float kSpotLighAtten2 = 0.0f;						 // ���������p�����[�^2
}

/// <summary>
/// ���C�g����
/// </summary>
namespace Light
{
	int m_spotLight; // �X�|�b�g���C�g

	/// <summary>
	///	���C�g�Z�b�g
	/// </summary>
	void SetLight();


	/// <summary>
	/// ���C�g�폜
	/// </summary>
	void DeleteLight()
	{
		DeleteLightHandleAll();
	}


	/// <summary>
	/// ���C�g�X�V
	/// </summary>
	void UpdateLight()
	{
		// TODO:�J��������̌�����ݒ肷��
		SetLightPositionHandle(m_spotLight, GetCameraPosition());
	}
}