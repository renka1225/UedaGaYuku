#include "DxLib.h"
#include "Player.h"
#include "Stage.h"
#include "UIBattle.h"
#include "EffectManager.h"
#include "LoadData.h"
#include "DebugDraw.h"
#include "EnemyNinja.h"

// �萔
namespace
{
	// �G���
	const char* const kfileName = "data/Model/Chara/Ninja.mv1";	// �G�̃t�@�C����
	constexpr float kScale = 0.3f;								// �g�嗦
	constexpr int kIntervalTime = 180;							// ��Ԃ��X�V����܂ł̎���
	const VECTOR kInitPos = VGet(2660, 69.0f, 4280.0f);			// �����ʒu
}

/// <summary>
/// �R���X�g���N�^
/// </summary>
EnemyNinja::EnemyNinja()
{
	// �L�����N�^�[����ǂݍ���
	m_pLoadData = std::make_shared<LoadData>(*this, static_cast<int>(CharaType::kEnemyNinja));
	m_pUIBattle = std::make_shared<UIBattle>(m_status.maxHp);

	m_hp = m_status.maxHp;
	m_pos = kInitPos;
	m_moveSpeed = m_status.maxMoveSpeed;
	m_modelHandle = MV1LoadModel(kfileName);
	MV1SetScale(m_modelHandle, VGet(kScale, kScale, kScale));
	MV1SetPosition(m_modelHandle, kInitPos);
}


/// <summary>
/// �f�X�g���N�^
/// </summary>
EnemyNinja::~EnemyNinja()
{
	MV1DeleteModel(m_modelHandle);
}


/// <summary>
///  ������
/// </summary>
/// <param name="pos">�����ʒu</param>
void EnemyNinja::Init(std::shared_ptr<EffectManager> pEffect, VECTOR pos)
{
	m_pos = pos;
	m_pEffect = pEffect;
	MV1SetPosition(m_modelHandle, m_pos);
	m_pEffect->Init();	// �G�t�F�N�g�̏�����
}


/// <summary>
/// �X�V
/// </summary>
/// <param name="player">�v���C���[�Q��</param>
/// <param name="stage">�X�e�[�W�Q��</param>
void EnemyNinja::Update(Player& player, Stage& stage, SceneStageBase& sceneStage)
{
	// �ړ��p�����[�^��ݒ肷��
	VECTOR	upMoveVec;		// ��{�^������͂������Ƃ��̃v���C���[�̈ړ������x�N�g��
	VECTOR	leftMoveVec;	// ���{�^������͂������Ƃ��̃v���C���[�̈ړ������x�N�g��
	VECTOR	moveVec;		// ���̃t���[���̈ړ��x�N�g��

	// �G�l�~�[�̏�Ԃ��X�V
	CharacterBase::State prevState = m_currentState;

	// �G�̈ʒu����v���C���[�ʒu�܂ł̃x�N�g�������߂�
	m_eToPDirVec = VSub(player.GetPos(), m_pos);

	// ��Ԃ��X�V����
	m_currentState = UpdateState(player, sceneStage, upMoveVec, leftMoveVec, moveVec);

	// �v���C���[�Ƃ̓����蔻����`�F�b�N����
	player.CheckHitEnemyCol(*this, VGet(m_pos.x, m_pos.y + m_colInfo.bodyHeight, m_pos.z), m_pos, m_colInfo.bodyRadius);

	UpdateAnimState(prevState);		// �A�j���[�V������Ԃ��X�V
	UpdateAngle();					// �p�x���X�V
	UpdateGuard();					// �K�[�h��Ԃ��X�V
	Move(moveVec, player, stage);	// �ړ��x�N�g�������ɃG�l�~�[���ړ�������
	UpdateAnim();					// �A�j���[�V���������̍X�V
	UpdateCol();					// �����蔻��ʒu�X�V
	UpdatePosLog();					// �ʒu���O���X�V
	m_pUIBattle->UpdateHpBar();		// HP�o�[�̍X�V
	m_pEffect->Update();			// �G�t�F�N�g�X�V
}


/// <summary>
/// �`��
/// </summary>
void EnemyNinja::Draw()
{
	MV1DrawModel(m_modelHandle);
	m_pEffect->Draw();				// �G�t�F�N�g�`��

	// ��𒆂͎c����\������
	if (m_currentState == State::kAvoid)
	{
		DrawAfterImage();
	}

#ifdef _DEBUG
	DebugDraw debug;
	debug.DrawEnemyInfo(m_pos, m_hp, static_cast<int>(m_currentState));
	// �����蔻��`��
	debug.DrawBodyCol(m_col.bodyTopPos, m_col.bodyBottomPos, m_colInfo.bodyRadius); // �S�g
	debug.DrawAimCol(m_col.armStartPos, m_col.armEndPos, m_colInfo.aimRadius);		// �r
	debug.DrawLegCol(m_col.legStartPos, m_col.legEndPos, m_colInfo.legRadius);		// �r
#endif
}


/// <summary>
/// UI�`��
/// </summary>
void EnemyNinja::DrawUi()
{
	m_pUIBattle->DrawSilhouette(static_cast<int>(CharacterBase::CharaType::kEnemyNinja));	// �V���G�b�g�`��
	m_pUIBattle->DrawEnemyHp(m_hp);	// HP�Q�[�W��\��
}
