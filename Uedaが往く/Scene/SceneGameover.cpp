#include "Dxlib.h"
#include "Input.h"
#include "Vec2.h"
#include "Game.h"
#include "UI.h"
#include "Sound.h"
#include "Font.h"
#include "Player.h"
#include "Camera.h"
#include "Stage.h"
#include "SceneTitle.h"
#include "SceneSelectStage.h"
#include "SceneStage1.h"
#include "SceneStage2.h"
#include "SceneGameover.h"

// �萔
namespace
{
	constexpr int kTextColor = 0xffffff;		// �e�L�X�g�̐F
	constexpr int kBackColor = 0x1a0306;		// �w�i�̐F
	const Vec2 kHaibokuTextPos = { 670, 120 };	// �s�k�̃e�L�X�g�摜�\���ʒu
	const Vec2 kRetryTextPos = { 870, 630 };	// "���g���C"�\���ʒu
	const Vec2 kStageTextPos = { 720, 760 };	// "�X�e�[�W�I���ɂ��ǂ�"�\���ʒu
	const Vec2 kTitleTextPos = { 770, 890 };	// "�^�C�g���ɂ��ǂ�"�\���ʒu
	const Vec2 kCursorPos = { 720, 620 };		// �J�[�\���\���ʒu
	constexpr float kCursorMove = 130.0f;		// �J�[�\���̈ړ���

	constexpr int kStartFadeAlpha = 255; // �X�^�[�g���̃t�F�[�h�l
	constexpr int kFadeFrame = 2;		 // �t�F�[�h�ω���
}


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="pScene">�O�Ɏ��s���Ă����V�[��</param>
SceneGameover::SceneGameover(std::shared_ptr<SceneBase> pScene)
{
	m_fadeAlpha = kStartFadeAlpha;
	m_select = Select::kRetry;
	m_pPrevScene = pScene;
	m_textHandle = LoadGraph("data/UI/haiboku.png");
}


/// <summary>
/// �f�X�g���N�^
/// </summary>
SceneGameover::~SceneGameover()
{
	StopSoundMem(Sound::m_bgmHandle[static_cast<int>(Sound::BgmKind::kGameover)]);
	DeleteGraph(m_textHandle);
}


/// <summary>
/// ������
/// </summary>
void SceneGameover::Init()
{
}


/// <summary>
/// �X�V
/// </summary>
/// <param name="input">���͏��</param>
/// <returns></returns>
std::shared_ptr<SceneBase> SceneGameover::Update(Input& input)
{
	FadeOut(kFadeFrame); // �t�F�[�h�A�E�g

	UpdateSelect(input, Select::kSelectNum); 	// �I����ԍX�V
	m_pUI->Update();

	// BGM��炷
	if (!CheckSoundMem(Sound::m_bgmHandle[static_cast<int>(Sound::BgmKind::kGameover)]))
	{
		PlaySoundMem(Sound::m_bgmHandle[static_cast<int>(Sound::BgmKind::kGameover)], DX_PLAYTYPE_LOOP);
	}

	if (input.IsTriggered("OK"))
	{
		if (m_select == kRetry)
		{
			std::shared_ptr<Player> pPlayer = std::make_shared<Player>();
			std::shared_ptr<Camera> pCamera = std::make_shared<Camera>();
			std::shared_ptr<Stage> pStage = std::make_shared<Stage>();

			// MEMO:typeid�ŃN���X���擾����
			if (typeid(*m_pPrevScene) == typeid(SceneStage1))
			{
				FadeIn(kFadeFrame); // �t�F�[�h�C��
				return std::make_shared<SceneStage1>(pPlayer, pCamera, pStage); // �X�e�[�W1�Ɉړ�
			}
			if (typeid(*m_pPrevScene) == typeid(SceneStage2))
			{
				FadeIn(kFadeFrame); // �t�F�[�h�C��
				return std::make_shared<SceneStage2>(pPlayer, pCamera, pStage); // �X�e�[�W2�Ɉړ�
			}

		}
		else if (m_select == kStageSelect)
		{
			FadeIn(kFadeFrame); // �t�F�[�h�C��
			return std::make_shared<SceneSelectStage>(); // �X�e�[�W�I����ʂɈړ�
		}
		else if (m_select == kTitle)
		{
			FadeIn(kFadeFrame); // �t�F�[�h�C��
			return std::make_shared<SceneTitle>();	// �^�C�g����ʂɈړ�
		}
	}

	return shared_from_this();	// ���g��shared_ptr��Ԃ�
}


/// <summary>
/// �`��
/// </summary>
void SceneGameover::Draw()
{
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, kBackColor, true);

	// �s�k�̕�����\��
	DrawGraphF(kHaibokuTextPos.x, kHaibokuTextPos.y, m_textHandle, true);

	// �J�[�\���\��
	m_pUI->DrawCursor(kCursorPos, m_select, kCursorMove);

	// �I�����ڂ�\��
	DrawStringFToHandle(kRetryTextPos.x, kRetryTextPos.y,
		"���g���C", kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kGameover)]);
	DrawStringFToHandle(kStageTextPos.x, kStageTextPos.y,
		"�X�e�[�W�I���ɂ��ǂ�", kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kGameover)]);
	DrawStringFToHandle(kTitleTextPos.x, kTitleTextPos.y,
		"�^�C�g���ɂ��ǂ�", kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kGameover)]);

	DrawFade();	// �t�F�[�h�C���A�E�g�`��

#ifdef _DEBUG	// �f�o�b�O�\��
	// ���݂̃V�[��
	DrawString(0, 0, "�Q�[���I�[�o�[���", 0xffffff);
	// ���S��
	//DrawLine(Game::kScreenWidth * 0.5, 0, Game::kScreenWidth * 0.5, Game::kScreenHeight, 0x0000ff);
#endif
}