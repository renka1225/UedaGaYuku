#include "DxLib.h"
#include "Player.h"
#include "Camera.h"
#include "Stage.h"
#include "Input.h"
#include "SceneTitle.h"
#include "SceneSelectStage.h"
#include "SceneOption.h"
#include "SceneStage1.h"
#include "SceneStage2.h"
#include "SceneClear.h"
#include "SceneGameover.h"
#include "SceneDebug.h"

// �萔
namespace
{
	constexpr int kTextColor = 0xffffff;		// �����F
	constexpr int kSelectTextColor = 0xff0000;	// �I�𒆂̕����F
}

/// <summary>
/// �R���X�g���N�^
/// </summary>
SceneDebug::SceneDebug()
{
}


/// <summary>
/// �X�V
/// </summary>
/// <param name="input">���͏��</param>
/// <returns></returns>
std::shared_ptr<SceneBase> SceneDebug::Update(Input& input)
{
	// �I����ԍX�V
	UpdateSelect(input, kSelectNum);

	// �J��
	if (input.IsTriggered("OK"))
	{
		std::shared_ptr<Player> pPlayer = std::make_shared<Player>();
		std::shared_ptr<Camera> pCamera = std::make_shared<Camera>();
		std::shared_ptr<Stage> pStage = std::make_shared<Stage>();

		if (m_select == SelectScene::kTitle)
		{
			return std::make_shared<SceneTitle>();
		}
		else if (m_select == SelectScene::kStageSelect)
		{
			return std::make_shared<SceneSelectStage>();
		}
		else if (m_select == SelectScene::kOption)
		{
			return std::make_shared<SceneOption>(shared_from_this());
		}
		else if (m_select == SelectScene::kStage1)
		{
			return std::make_shared<SceneStage1>(pPlayer, pCamera, pStage);
		}
		else if (m_select == SelectScene::kStage2)
		{
			return std::make_shared<SceneStage2>(pPlayer, pCamera, pStage);
		}
		else if (m_select == SelectScene::kClear)
		{
			return std::make_shared<SceneClear>();
		}
		else if (m_select == SelectScene::kGameover)
		{
			return std::make_shared<SceneGameover>(shared_from_this());
		}
	}

	return shared_from_this();
}

/// <summary>
/// �`��
/// </summary>
void SceneDebug::Draw()
{
	int titleColor = kTextColor;
	int stageselectColor = kTextColor;
	int optionColor = kTextColor;
	int stage1Color = kTextColor;
	int stage2Color = kTextColor;
	int clearColor = kTextColor;
	int gameoverColor = kTextColor;

	if (m_select == SelectScene::kTitle)	titleColor = kSelectTextColor;
	if (m_select == SelectScene::kStageSelect) stageselectColor = kSelectTextColor;
	if (m_select == SelectScene::kOption) optionColor = kSelectTextColor;
	if (m_select == SelectScene::kStage1) stage1Color = kSelectTextColor;
	if (m_select == SelectScene::kStage2) stage2Color = kSelectTextColor;
	if (m_select == SelectScene::kClear) clearColor = kSelectTextColor;
	if (m_select == SelectScene::kGameover) gameoverColor = kSelectTextColor;

	DrawString(0, 20, "�^�C�g��", titleColor);
	DrawString(0, 40, "�X�e�[�W�I��", stageselectColor);
	DrawString(0, 60, "�I�v�V����", optionColor);
	DrawString(0, 80, "�X�e�[�W1", stage1Color);
	DrawString(0, 100, "�X�e�[�W2", stage2Color);
	DrawString(0, 120, "�N���A", clearColor);
	DrawString(0, 140, "�Q�[���I�[�o�[", gameoverColor);
}