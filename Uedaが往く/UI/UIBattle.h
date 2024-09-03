#pragma once
#include "UI.h"

/// <summary>
/// �o�g�����ɕ\������UI���Ǘ�����
/// </summary>
class UIBattle : public UI
{
public:
	UIBattle();
	UIBattle(float maxHp);
	virtual ~UIBattle();
	void UpdateHpBar();				// HP�\�����X�V����
	void SetDamageTimer();			// �_���[�W���󂯂��ۂɃ^�C�}�[���Z�b�g����
	void OnDamage(float damage);	// �󂯂��_���[�W�ʂ��v�Z����
	void DrawStartProduction(int time, int matchNum, int maxMatch); // �X�^�[�g���̉��o��\��
	void DrawPlayerHP(float currentHp);								// �v���C���[��HP�o�[��\��
	void DrawPlayerGauge(float currentGauge, float MaxGauge);		// �v���C���[�̃Q�[�W�o�[��\��
	void DrawEnemyHp(float currentHp);								// �G��HP�o�[��\��
	void DrawSilhouette(int charType);								// �V���G�b�g��\��
	void DrawSpecialAttack();										// �K�E�Z�̃e�L�X�g�\��
	void DrawOperation();											// ���������\��
	void DrawTutoButtonText();										// �`���[�g���A����ʂ̃{�^���\��

private:
	float m_decreaseHp;				// �_���[�W���󂯂����HP
	float m_currentHp;				// ���݂�HP
	float m_damage;					// �󂯂��_���[�W��
	float m_maxHp;					// �ő�HP
	int m_intervalTime;				// HP�o�[����������܂ł̎���
	int m_gaugeBarHandle;			// �Q�[�W�o�[�̉摜
	int m_silhouetteHandle;			// �L�����N�^�[�̃V���G�b�g�摜
	int m_fightTextHandle;			// "Fight"�̃e�L�X�g�摜
	int m_numTextHandle;			// �����̉摜
	std::vector<int> m_handle;		// �n���h��

	// �摜�̎��
	enum HandleKind
	{
		kGaugeBar,	 // �Q�[�W�o�[
		kSilhouette, // �L�����N�^�[�̃V���G�b�g
		kFightText,	 // "Fight!"�̃e�L�X�g
		kNumText,	 // ����
		kHandleNum	 // �n���h���̎��
	};

	// ��������ŕ\�����鏇��
	enum OperationOrder
	{
		kMove,			// �ړ�
		kCameraMove,	// �J�����ړ�
		kPunch,			// �p���`
		kKick,			// �L�b�N
		kAvoid,			// ���
		kGuard,			// �K�[�h
		kRockon,		// ���b�N�I��
		kPause,			// �|�[�Y
	};
};
