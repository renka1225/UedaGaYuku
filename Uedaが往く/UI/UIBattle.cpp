#include "DxLib.h"
#include "Vec2.h"
#include "Font.h"
#include "UI.h"
#include "CharacterBase.h"
#include "UIBattle.h"
#include <string>

// �萔
namespace
{
	const Vec2 kESilhouettePos = { 1700.0f, 870.0f };		// �G�L�����N�^�[�̃V���G�b�g�ʒu
	constexpr int kSilhouetteWidth = 268;					// �L�����N�^�[�̃V���G�b�g�摜��
	constexpr int kSilhouetteHeight = 213;					// �L�����N�^�[�̃V���G�b�g�摜����

	constexpr int kHpColor = 0xff0000;						// HP�o�[�̐F
	constexpr int kDamageHpColor = 0xffd700;				// �_���[�W����HP�o�[�̐F
	constexpr int kpGaugeColor = 0x0000ff;					// �Q�[�W�o�[�̐F
	constexpr int kIntervalTime = 50;						// HP�o�[����������܂ł̎���

	/*�����J�n��*/
	constexpr int kFightTextDispStart = 80;					 // "Fight"�̃e�L�X�g��\�����n�߂鎞��
	const Vec2 kFightTextPos = { 960, 550 };				 // "Fight"�̃e�L�X�g�ʒu
	constexpr float kFightTextScele = 0.6f;					 // "Fight"�̃e�L�X�g�T�C�Y
	const Vec2 kMatcheNumTextPos = { 850, 600 };			 // ���݂̎������\���ʒu
	constexpr int kMatchNumTextWidth = 260;					 // 1������̃e�L�X�g�̕�
	constexpr int kMatchNumTextInterval = 70;				 // �e�L�X�g�̕\���Ԋu
	constexpr int kTextAdj = 60;							 // �e�L�X�g�̕\���Ԋu����
	constexpr float kMatchNumTextScele = 0.5f;				 // �������̃e�L�X�g�T�C�Y

	/*�v���C���[UI*/
	const Vec2 kPlayerHpBarLT = { 25.0f, 50.0f };			 // HP�o�[����ʒu
	const Vec2 kPlayerHpBarRB = { 1000.0f, 80.0f };			 // HP�o�[�E���ʒu
	const Vec2 kPlayerCurrentHpLT = { 50.0f, 56.0f };		 // ���݂�HP����ʒu
	constexpr float kPlayerHpWidth = 907.0f;				 // HP�o�[�̉���
	constexpr float kPlayerHpHeight = 18.0f;				 // HP�o�[�̏c��
		
	const Vec2 kPlayerGaugeBarLT = { 25.0f, 95.0f };		 // �Q�[�W�o�[����ʒu
	const Vec2 kPlayerGaugeBarRB = { 800.0f, 120.0f };		 // �Q�[�W�o�[�E���ʒu
	const Vec2 kPlayerCurrentGaugeLT = { 40.0f, 100.0f };	 // ���݂̃Q�[�W�ʍ���ʒu
	constexpr float kPlayerGaugeWidth = 727.0f;				 // �Q�[�W�o�[�̉���
	constexpr float kPlayerGaugeHeight = 15.0f;				 // �Q�[�W�o�[�̏c��

	/*�GUI*/
	const Vec2 kEnemyHpBarLT = { 850.0f, 970.0f };			 // HP�o�[����ʒu
	const Vec2 kEnemyHpBarRB = { 1850.0f, 1000.0f };		 // HP�o�[�E���ʒu
	const Vec2 kEnemyCurrentHpLT = { 885.0f, 976.0f };		 // ���݂�HP����ʒu
	constexpr float kEnemyHpWidth = 920.0f;					 // HP�o�[�̉���
	constexpr float kEnemyHpHeight = 17.0f;					 // HP�o�[�̏c��

	/*����������*/
	const Vec2 kOperationFramePos = { 1720.0f, 280.0f };	 // �g�\���ʒu
	constexpr float kOperationWidth = 300.0f;				 // �g�̉���
	constexpr float kOperationHeight = 350.0f;				 // �g�̏c��
	constexpr int kOperationBackColor = 0x000000;			 // �g�̔w�i�F
	const Vec2 kOperationTextPos = { 1730.0f, 300.0f };		 // �e�L�X�g�̕\���ʒu
	const Vec2 kOperationButtonPos = { 1880.0f, 320.0f };	 // �{�^���ʒu
	constexpr int kButtonSize = 32;						 	 // �{�^���摜�̃T�C�Y
	constexpr float kOperationButtonScale = 1.0f;		 	 // �{�^���̊g�嗦
	constexpr float kOperationInterval = 40.0f;				 // �\���Ԋu
	constexpr int kTextColor = 0xffffff;					 // �e�L�X�g�̐F

	/*�K�E�Z*/
	const Vec2 kSpecialAttackButtonPos = { 760.0f, 140.0f }; // �{�^���ʒu 
	constexpr float kSpecialAttackButtonScale = 1.2f;		 // �{�^���g�嗦
	const Vec2 kSpecialAttackTextPos = { 620.0f, 120.0f };	 // �e�L�X�g�ʒu
	constexpr int kSpecialAttackTextColor = 0x1470cc;		 // �e�L�X�g�̐F
	constexpr int kSpecialAttackTextEdgeColor = 0x0a3866;	 // �e�L�X�g���̐F
	constexpr int kMaxPal = 255;							 // �ő���Z�l

	/*�`���[�g���A��*/
	const Vec2 kTutoTextPos = { 1300.0f, 770.0f };			// �e�L�X�g�ʒu
	const Vec2 kTutoButtonPos = { 1390.0f, 790.0f };		// �{�^���ʒu
	constexpr float kTutoButtonScale = 1.2f;				// �{�^���g�嗦
}

/// <summary>
/// �R���X�g���N�^
/// </summary>
UIBattle::UIBattle():
	m_decreaseHp(0),
	m_currentHp(0),
	m_maxHp(0),
	m_damage(0.0f),
	m_intervalTime(0)
{
	m_handle.resize(HandleKind::kHandleNum);
	m_handle[HandleKind::kFightText] = LoadGraph("data/UI/Fight!.png");
	m_handle[HandleKind::kNumText] = LoadGraph("data/UI/number.png");
	m_handle[HandleKind::kGaugeBar] = LoadGraph("data/UI/Gauge.png");
	m_handle[HandleKind::kSilhouette] = LoadGraph("data/UI/silhouette.png");
}


/// <summary>
/// �������R���X�g���N�^
/// </summary>
UIBattle::UIBattle(float maxHp):
	m_decreaseHp(maxHp),
	m_currentHp(maxHp),
	m_maxHp(maxHp),
	m_damage(0.0f),
	m_intervalTime(0)
{
	m_handle.resize(HandleKind::kHandleNum);
	m_handle[HandleKind::kFightText] = LoadGraph("data/UI/Fight!.png");
	m_handle[HandleKind::kNumText] = LoadGraph("data/UI/number.png");
	m_handle[HandleKind::kGaugeBar] = LoadGraph("data/UI/Gauge.png");
	m_handle[HandleKind::kSilhouette] = LoadGraph("data/UI/silhouette.png");
}


/// <summary>
/// �f�X�g���N�^
/// </summary>
UIBattle::~UIBattle()
{
	for (auto& handle : m_handle)
	{
		DeleteGraph(handle);
	}
}


/// <summary>
/// �X�V
/// </summary>
void UIBattle::UpdateHpBar()
{
	if (m_intervalTime >= 0)
	{
		m_intervalTime--;
	}
	if (m_intervalTime < 0)
	{
		m_currentHp -= m_damage;
		m_damage = 0.0f;
	}
}


/// <summary>
/// �_���[�W���󂯂��ۂɃ^�C�}�[���Z�b�g����
/// </summary>
void UIBattle::SetDamageTimer()
{
	if (m_intervalTime < 0)
	{
		m_intervalTime = kIntervalTime;
	}
}


/// <summary>
/// �_���[�W���󂯂����̏���
/// </summary>
/// <param name="damage">�󂯂��_���[�W��</param>
void UIBattle::OnDamage(float damage)
{
	m_damage += damage;
	SetDamageTimer();
}


/// <summary>
/// �X�^�[�g���̉��o�\��
/// </summary>
/// <param name="time">�o�ߎ���</param>
/// <param name="matchNum">���݂̎�����</param>
/// <param name="maxMatch">�ő厎����</param>
void UIBattle::DrawStartProduction(int time, int matchNum, int maxMatch)
{
	if (time > kFightTextDispStart)
	{
		int sizeW, sizeH;
		GetGraphSize(m_handle[HandleKind::kNumText], &sizeW, &sizeH);
		// ���݂̎�������\��
		DrawRectRotaGraphF(kMatcheNumTextPos.x, kMatcheNumTextPos.y,
			kMatchNumTextWidth * matchNum, 0, kMatchNumTextWidth, sizeH,
			kMatchNumTextScele, 0.0f, m_handle[HandleKind::kNumText], true);
		// /�\��
		DrawRectRotaGraphF(kMatcheNumTextPos.x + kMatchNumTextInterval, kMatcheNumTextPos.y,
			sizeW - kMatchNumTextWidth, 0, kMatchNumTextWidth, sizeH,
			kMatchNumTextScele, 0.0f, m_handle[HandleKind::kNumText], true);
		// �ő厎������\��
		DrawRectRotaGraphF(kMatcheNumTextPos.x + kMatchNumTextInterval * 2 + kTextAdj, kMatcheNumTextPos.y,
			kMatchNumTextWidth * (maxMatch - 1), 0, kMatchNumTextWidth, sizeH,
			kMatchNumTextScele, 0.0f, m_handle[HandleKind::kNumText], true);
	}
	// "Fight!"�̕�����\��
	else if (time < kFightTextDispStart && time > 0)
	{
		int sizeW, sizeH;
		GetGraphSize(m_handle[HandleKind::kFightText], &sizeW, &sizeH);
		DrawRectRotaGraphF(kFightTextPos.x, kFightTextPos.y, 0, 0, sizeW, sizeH, kFightTextScele, 0.0f, m_handle[HandleKind::kFightText], true);
	}
}


/// <summary>
/// �v���C���[��HP�o�[�\��
/// </summary>
/// <param name="currentHp">���݂�HP</param>
/// <param name="MaxHp">�ő�HP</param>
void UIBattle::DrawPlayerHP(float currentHp)
{
	// �\������Q�[�W�ʂ��v�Z����
	float hpRatio = currentHp / m_maxHp;
	float decreaseHpRatio = (currentHp + m_damage) / m_maxHp;
	float hpLength = kPlayerHpWidth * hpRatio;
	float decreaseHpLength = kPlayerHpWidth * decreaseHpRatio;

	// �o�[�̔w�i����
	DrawExtendGraphF(kPlayerHpBarLT.x, kPlayerHpBarLT.y, kPlayerHpBarRB.x, kPlayerHpBarRB.y, m_handle[HandleKind::kGaugeBar], true);
	// �_���[�W���󂯂��ۂɕ\������
	if (m_intervalTime > 0)
	{
		DrawBoxAA(kPlayerCurrentHpLT.x, kPlayerCurrentHpLT.y, kPlayerCurrentHpLT.x + decreaseHpLength, kPlayerCurrentHpLT.y + kPlayerHpHeight, kDamageHpColor, true);
	}
	// ���݂�HP�o�[
	DrawBoxAA(kPlayerCurrentHpLT.x, kPlayerCurrentHpLT.y, kPlayerCurrentHpLT.x + hpLength, kPlayerCurrentHpLT.y + kPlayerHpHeight, kHpColor, true);
}


/// <summary>
/// �v���C���[�̃Q�[�W�o�[�\��
/// </summary>
/// <param name="currentGauge">���݂̃Q�[�W��</param>
/// <param name="MaxGauge">�ő�Q�[�W��</param>
void UIBattle::DrawPlayerGauge(float currentGauge, float MaxGauge)
{
	// �\������Q�[�W�ʂ��v�Z����
	float hpRatio = currentGauge / MaxGauge;
	float hpLength = kPlayerGaugeWidth * hpRatio;

	// �o�[�̔w�i����
	DrawExtendGraphF(kPlayerGaugeBarLT.x, kPlayerGaugeBarLT.y, kPlayerGaugeBarRB.x, kPlayerGaugeBarRB.y, m_handle[HandleKind::kGaugeBar], true);
	DrawBoxAA(kPlayerCurrentGaugeLT.x, kPlayerCurrentGaugeLT.y, kPlayerCurrentGaugeLT.x + hpLength, kPlayerCurrentGaugeLT.y + kPlayerGaugeHeight, kpGaugeColor, true);
}


/// <summary>
/// �G��HP�o�[��\��
/// </summary>
/// <param name="currentHp">���݂�HP</param>
void UIBattle::DrawEnemyHp(float currentHp)
{
	// �\������Q�[�W�ʂ��v�Z����
	float hpRatio = currentHp / m_maxHp;
	float decreaseHpRatio = (currentHp + m_damage) / m_maxHp;
	float hpLength = kEnemyHpWidth * hpRatio;
	float decreaseHpLength = kEnemyHpWidth * decreaseHpRatio;

	// �o�[�̔w�i����
	DrawExtendGraphF(kEnemyHpBarLT.x, kEnemyHpBarLT.y, kEnemyHpBarRB.x, kEnemyHpBarRB.y, m_handle[HandleKind::kGaugeBar], true);
	// �_���[�W���󂯂����̃o�[
	if (m_intervalTime > 0)
	{
		DrawBoxAA(kEnemyCurrentHpLT.x, kEnemyCurrentHpLT.y, kEnemyCurrentHpLT.x + decreaseHpLength, kEnemyCurrentHpLT.y + kEnemyHpHeight, kDamageHpColor, true);
	}
	DrawBoxAA(kEnemyCurrentHpLT.x, kEnemyCurrentHpLT.y, kEnemyCurrentHpLT.x + hpLength, kEnemyCurrentHpLT.y + kEnemyHpHeight, kHpColor, true);
}


/// <summary>
/// �V���G�b�g�`��
/// </summary>
void UIBattle::DrawSilhouette(int charType)
{
	DrawRectRotaGraphF(kESilhouettePos.x, kESilhouettePos.y, kSilhouetteWidth * charType, 0, kSilhouetteWidth, kSilhouetteHeight, 1.0f, 0.0f, m_handle[HandleKind::kSilhouette], true);
}


/// <summary>
/// �K�E�Z�̃e�L�X�g�\��
/// </summary>
void UIBattle::DrawSpecialAttack()
{
	DrawStringFToHandle(kSpecialAttackTextPos.x, kSpecialAttackTextPos.y, "�K�E�Z", kSpecialAttackTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kSpecialAttack)], kSpecialAttackTextEdgeColor);
	SetDrawBlendMode(DX_BLENDMODE_ADD, kMaxPal);
	DrawStringFToHandle(kSpecialAttackTextPos.x, kSpecialAttackTextPos.y, "�K�E�Z", kSpecialAttackTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kSpecialAttack)]);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	// �{�^���摜�\��
	DrawRectRotaGraphF(kSpecialAttackButtonPos.x, kSpecialAttackButtonPos.y, kButtonSize * ButtonKind::kBButton, 0, kButtonSize, kButtonSize, kSpecialAttackButtonScale, 0.0f, m_buttonHandle, true);
}


/// <summary>
/// ���������\��
/// </summary>
void UIBattle::DrawOperation()
{
	// �w�i�𔖂��\������
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	DrawBoxAA(kOperationFramePos.x, kOperationFramePos.y, kOperationFramePos.x + kOperationWidth, kOperationFramePos.y + kOperationHeight, kOperationBackColor, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	// �e�L�X�g�\��
	DrawStringFToHandle(kOperationTextPos.x, kOperationTextPos.y + kOperationInterval * OperationOrder::kMove,
		"�ړ�", kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kOperation)]);
	DrawStringFToHandle(kOperationTextPos.x, kOperationTextPos.y + kOperationInterval * OperationOrder::kCameraMove,
		"�J�����ړ�", kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kOperation)]);
	DrawStringFToHandle(kOperationTextPos.x, kOperationTextPos.y + kOperationInterval * OperationOrder::kPunch,
		"�p���`", kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kOperation)]);
	DrawStringFToHandle(kOperationTextPos.x, kOperationTextPos.y + kOperationInterval * OperationOrder::kKick,
		"�L�b�N", kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kOperation)]);
	DrawStringFToHandle(kOperationTextPos.x, kOperationTextPos.y + kOperationInterval * OperationOrder::kAvoid,
		"���", kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kOperation)]);
	DrawStringFToHandle(kOperationTextPos.x, kOperationTextPos.y + kOperationInterval * OperationOrder::kGuard,
		"�K�[�h", kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kOperation)]);
	DrawStringFToHandle(kOperationTextPos.x, kOperationTextPos.y + kOperationInterval * OperationOrder::kRockon,
		"���b�N�I��", kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kOperation)]);
	DrawStringFToHandle(kOperationTextPos.x, kOperationTextPos.y + kOperationInterval * OperationOrder::kPause,
		"�|�[�Y", kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kOperation)]);

	// �{�^���摜�\��
	DrawRectRotaGraphF(kOperationButtonPos.x, kOperationButtonPos.y + kOperationInterval * OperationOrder::kMove,
		kButtonSize * ButtonKind::kRStick, 0, kButtonSize, kButtonSize, kOperationButtonScale, 0.0f, m_buttonHandle, true);		// R�X�e�B�b�N
	DrawRectRotaGraphF(kOperationButtonPos.x, kOperationButtonPos.y + kOperationInterval * OperationOrder::kCameraMove,
		kButtonSize * ButtonKind::kLStick, 0, kButtonSize, kButtonSize, kOperationButtonScale, 0.0f, m_buttonHandle, true);		// L�X�e�B�b�N
	DrawRectRotaGraphF(kOperationButtonPos.x, kOperationButtonPos.y + kOperationInterval * OperationOrder::kPunch,
		kButtonSize * ButtonKind::kXButton, 0, kButtonSize, kButtonSize, kOperationButtonScale, 0.0f, m_buttonHandle, true);	// X
	DrawRectRotaGraphF(kOperationButtonPos.x, kOperationButtonPos.y + kOperationInterval * OperationOrder::kKick,
		kButtonSize * ButtonKind::kYButton, 0, kButtonSize, kButtonSize, kOperationButtonScale, 0.0f, m_buttonHandle, true);	// Y
	DrawRectRotaGraphF(kOperationButtonPos.x, kOperationButtonPos.y + kOperationInterval * OperationOrder::kAvoid,
		kButtonSize * ButtonKind::kAButton, 0, kButtonSize, kButtonSize, kOperationButtonScale, 0.0f, m_buttonHandle, true);	// A
	DrawRectRotaGraphF(kOperationButtonPos.x, kOperationButtonPos.y + kOperationInterval * OperationOrder::kGuard,
		kButtonSize * ButtonKind::kLBButton, 0, kButtonSize, kButtonSize, kOperationButtonScale, 0.0f, m_buttonHandle, true);	// LB
	DrawRectRotaGraphF(kOperationButtonPos.x, kOperationButtonPos.y + kOperationInterval * OperationOrder::kRockon,
		kButtonSize * ButtonKind::kRBButton, 0, kButtonSize, kButtonSize, kOperationButtonScale, 0.0f, m_buttonHandle, true);	// RB
	DrawRectRotaGraphF(kOperationButtonPos.x, kOperationButtonPos.y + kOperationInterval * OperationOrder::kPause,
		kButtonSize * ButtonKind::kMenuButton, 0, kButtonSize, kButtonSize, kOperationButtonScale, 0.0f, m_buttonHandle, true);	// Menu
}


/// <summary>
/// �`���[�g���A����ʂ̃{�^���\��
/// </summary>
void UIBattle::DrawTutoButtonText()
{
	// �e�L�X�g�\��
	DrawStringFToHandle(kTutoTextPos.x, kTutoTextPos.y,
		"����", kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kTutoButton)]);

	// �{�^���摜�\��
	DrawRectRotaGraphF(kTutoButtonPos.x, kTutoButtonPos.y, kButtonSize * ButtonKind::kAButton, 0, kButtonSize, kButtonSize, kTutoButtonScale, 0.0f, m_buttonHandle, true);
}
