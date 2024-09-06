#include "DxLib.h"
#include "Input.h"
#include "Game.h"
#include "UI.h"
#include "UIBattle.h"
#include "EffectManager.h"
#include "Sound.h"
#include "Light.h"
#include "Player.h"
#include "EnemyBase.h"
#include "Camera.h"
#include "Stage.h"
#include "SceneClear.h"
#include "SceneGameover.h"
#include "SceneStageBase.h"

namespace
{
	const VECTOR kPlayerInitPos = VGet(2600.0f, 69.0f, 4240.0f);  // �v���C���[�̏����ʒu
	const VECTOR kEnemyInitPos = VGet(2660, 69.0f, 4280.0f);	  // �G�̏����ʒu
	constexpr int kChangeColorTime = 220;						  // ��ʂ̕\����ύX���鎞��
	constexpr int kClearStagingTime = 240;						  // �N���A���o�̎���
	constexpr int kNextBattleTime = 300;						  // ���̎������n�܂�܂ł̎���
	constexpr int kBattleEndSoundTime = 60;						  // �R���O��SE��炷����
	constexpr int kClearBackColor = 0x0f2699;					  // �N���A���̔w�i�F
	constexpr int kMULAPal = 240;								  // ��Z�u�����h�l
	constexpr int kAddPal = 80;									  // ���Z�u�����h�l
	
	/*�e*/
	constexpr int kShadowMapSize = 4096;							  // �쐬����V���h�E�}�b�v�̃T�C�Y
	const VECTOR kShadowAreaMinPos = VGet(2200.0f, 65.0f, 3800.0f);	  // �V���h�E�}�b�v�ɕ`�悷��ŏ��͈�
	const VECTOR kShadowAreaMaxPos = VGet(3000.0f, 100.0f, 5000.0f);  // �V���h�E�}�b�v�ɕ`�悷��ő�͈�

	constexpr int kStartFadeAlpha = 255; // �X�^�[�g���̃t�F�[�h�l
	constexpr int kFadeFrame = 8;		 // �t�F�[�h�ω���
}


/// <summary>
/// �R���X�g���N�^
/// </summary>
SceneStageBase::SceneStageBase() :
	m_battleNum(0),
	m_nextBattleTime(kNextBattleTime),
	m_clearStagingTime(kClearStagingTime),
	m_elapsedTime(0),
	m_isPause(false)
{
	//m_pLight->Create(m_pPlayer);
	m_shadowMap = MakeShadowMap(kShadowMapSize, kShadowMapSize);
	// �V���h�E�}�b�v���z�肷�郉�C�g�̕������Z�b�g
	SetShadowMapLightDirection(m_shadowMap, GetLightPosition());
	// �V���h�E�}�b�v�ɕ`�悷��͈͂�ݒ�
	SetShadowMapDrawArea(m_shadowMap, kShadowAreaMinPos, kShadowAreaMaxPos);

	m_fadeAlpha = kStartFadeAlpha;
	m_pEffect = std::make_shared<EffectManager>();
	m_pLight = std::make_shared<Light>();
	m_clearBackHandle = LoadGraph("data/UI/clearBack.png");
}


/// <summary>
/// �������R���X�g���N�^
/// </summary>
/// <param name="pPlayer">�v���C���[�Q��</param>
/// <param name="pCamera">�J�����Q��</param>
/// <param name="pStage">�X�e�[�W�Q��</param>
SceneStageBase::SceneStageBase(std::shared_ptr<Player> pPlayer, std::shared_ptr<Camera> pCamera, std::shared_ptr<Stage> pStage):
	m_pPlayer(pPlayer),
	m_pCamera(pCamera),
	m_pStage(pStage),
	m_pEnemy(nullptr),
	m_pUIBattle(nullptr),
	m_battleNum(0),
	m_clearStagingTime(0),
	m_nextBattleTime(0),
	m_elapsedTime(0),
	m_isPause(false),
	m_shadowMap(-1),
	m_clearBackHandle(-1)
{
	//m_pLight->Create(m_pPlayer);
}


/// <summary>
/// �f�X�g���N�^
/// </summary>
SceneStageBase::~SceneStageBase()
{
	//m_pLight->Delete();
	DeleteShadowMap(m_shadowMap); // �V���h�E�}�b�v�̍폜
	DeleteGraph(m_clearBackHandle);
}


/// <summary>
/// ������
/// </summary>
void SceneStageBase::Init()
{
	if (!m_isPause)
	{
		m_pPlayer->Init(m_pEffect, kPlayerInitPos);
		m_pCamera->Init();
		m_pEnemy->Init(m_pEffect, kEnemyInitPos);
	}
	m_isPause = false;
}


/// <summary>
/// �`��
/// </summary>
void SceneStageBase::Draw()
{
	ShadowMap_DrawSetup(m_shadowMap); // �V���h�E�}�b�v�ւ̕`��̏���
	m_pStage->Draw();	 // �X�e�[�W�`��
	m_pPlayer->Draw();	 // �v���C���[�`��
	m_pEnemy->Draw();	 // �G�`��
	ShadowMap_DrawEnd(); // �V���h�E�}�b�v�ւ̕`����I��

	SetUseShadowMap(0, m_shadowMap); // �`��Ɏg�p����V���h�E�}�b�v��ݒ�
	m_pStage->Draw();	 // �X�e�[�W�`��
	m_pPlayer->Draw();	 // �v���C���[�`��
	m_pEnemy->Draw();	 // �G�`��
	SetUseShadowMap(0, -1); // �`��Ɏg�p����V���h�E�}�b�v�̐ݒ������

	m_pEnemy->DrawUi();			  // �G��UI�`��
	m_pUIBattle->DrawOperation(); // ���������\��

	// �N���A����ʂ̐F����ς���
	if (m_clearStagingTime < kClearStagingTime && m_clearStagingTime >= 0)
	{
		SetDrawBlendMode(DX_BLENDMODE_MULA, kMULAPal);
		DrawGraph(0, 0, m_clearBackHandle, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		SetDrawBlendMode(DX_BLENDMODE_ADD, kAddPal);
		DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, kClearBackColor, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	DrawFade();	// �t�F�[�h�C���A�E�g�`��

#ifdef _DEBUG
	//TestDrawShadowMap(m_shadowMap, 0, 0, 320, 240); // ��ʍ���ɃV���h�E�}�b�v���e�X�g�`��
	DrawFormatString(0, 140, 0xffffff, "�o�ߎ���:%d", m_elapsedTime); // �o�ߎ��ԕ`��
	DrawFormatString(0, 180, 0xffffff, "�J�����ʒu(X:%.2f, Y:%.2f, Z:%.2f)", GetCameraPosition().x, GetCameraPosition().y, GetCameraPosition().z);
	m_pLight->Draw(); // ���C�g�ʒu�`��
#endif
}


/// <summary>
/// �N���A���o���s��
/// </summary>
void SceneStageBase::ClearStaging()
{
	// SE��炷
	if (m_clearStagingTime >= kClearStagingTime - kBattleEndSoundTime)
	{
		if (!CheckSoundMem(Sound::m_seHandle[static_cast<int>(Sound::SeKind::kBattleEnd)]))
		{
			PlaySoundMem(Sound::m_seHandle[static_cast<int>(Sound::SeKind::kBattleEnd)], DX_PLAYTYPE_BACK);
		}
	}
	else
	{
		if (!CheckSoundMem(Sound::m_seHandle[static_cast<int>(Sound::SeKind::kClearCheers)]))
		{
			PlaySoundMem(Sound::m_seHandle[static_cast<int>(Sound::SeKind::kClearCheers)], DX_PLAYTYPE_BACK);
		}
	}

	if (m_clearStagingTime >= kClearStagingTime - kChangeColorTime)
	{
		m_clearStagingTime--;
		return;
	}

	// �N���A���o�����Z�b�g
	m_clearStagingTime = 0;
	StopSoundMem(Sound::m_seHandle[static_cast<int>(Sound::SeKind::kClearCheers)]);
}


/// <summary>
/// �G��|���Ď��������n�܂�O�̏���
/// </summary>
void SceneStageBase::UpdateNextBattle()
{
	m_nextBattleTime = kNextBattleTime;
	m_clearStagingTime = kClearStagingTime;
	m_pUIBattle->ResetStartProduction();
	m_pUIBattle->SetEnemyKind(m_pEnemy->GetEnemyType());
	// �v���C���[�̈ʒu�A�J�����ʒu���ŏ��̏�Ԃɖ߂�
	m_pPlayer->Recovery();
	Init();

	FadeIn(kFadeFrame); // �t�F�[�h�C��
}