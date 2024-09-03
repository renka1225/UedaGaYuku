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

// 定数
namespace
{
	constexpr int kTextColor = 0xffffff;		// テキストの色
	constexpr int kBackColor = 0x1a0306;		// 背景の色
	const Vec2 kHaibokuTextPos = { 670, 120 };	// 敗北のテキスト画像表示位置
	const Vec2 kRetryTextPos = { 870, 630 };	// "リトライ"表示位置
	const Vec2 kStageTextPos = { 720, 760 };	// "ステージ選択にもどる"表示位置
	const Vec2 kTitleTextPos = { 770, 890 };	// "タイトルにもどる"表示位置
	const Vec2 kCursorPos = { 720, 620 };		// カーソル表示位置
	constexpr float kCursorMove = 130.0f;		// カーソルの移動量

	constexpr int kStartFadeAlpha = 255; // スタート時のフェード値
	constexpr int kFadeFrame = 2;		 // フェード変化量
}


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="pScene">前に実行していたシーン</param>
SceneGameover::SceneGameover(std::shared_ptr<SceneBase> pScene)
{
	m_fadeAlpha = kStartFadeAlpha;
	m_select = Select::kRetry;
	m_pPrevScene = pScene;
	m_textHandle = LoadGraph("data/UI/haiboku.png");
}


/// <summary>
/// デストラクタ
/// </summary>
SceneGameover::~SceneGameover()
{
	StopSoundMem(Sound::m_bgmHandle[static_cast<int>(Sound::BgmKind::kGameover)]);
	DeleteGraph(m_textHandle);
}


/// <summary>
/// 初期化
/// </summary>
void SceneGameover::Init()
{
}


/// <summary>
/// 更新
/// </summary>
/// <param name="input">入力状態</param>
/// <returns></returns>
std::shared_ptr<SceneBase> SceneGameover::Update(Input& input)
{
	FadeOut(kFadeFrame); // フェードアウト

	UpdateSelect(input, Select::kSelectNum); 	// 選択状態更新
	m_pUI->Update();

	// BGMを鳴らす
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

			// MEMO:typeidでクラスを取得する
			if (typeid(*m_pPrevScene) == typeid(SceneStage1))
			{
				FadeIn(kFadeFrame); // フェードイン
				return std::make_shared<SceneStage1>(pPlayer, pCamera, pStage); // ステージ1に移動
			}
			if (typeid(*m_pPrevScene) == typeid(SceneStage2))
			{
				FadeIn(kFadeFrame); // フェードイン
				return std::make_shared<SceneStage2>(pPlayer, pCamera, pStage); // ステージ2に移動
			}

		}
		else if (m_select == kStageSelect)
		{
			FadeIn(kFadeFrame); // フェードイン
			return std::make_shared<SceneSelectStage>(); // ステージ選択画面に移動
		}
		else if (m_select == kTitle)
		{
			FadeIn(kFadeFrame); // フェードイン
			return std::make_shared<SceneTitle>();	// タイトル画面に移動
		}
	}

	return shared_from_this();	// 自身のshared_ptrを返す
}


/// <summary>
/// 描画
/// </summary>
void SceneGameover::Draw()
{
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, kBackColor, true);

	// 敗北の文字を表示
	DrawGraphF(kHaibokuTextPos.x, kHaibokuTextPos.y, m_textHandle, true);

	// カーソル表示
	m_pUI->DrawCursor(kCursorPos, m_select, kCursorMove);

	// 選択項目を表示
	DrawStringFToHandle(kRetryTextPos.x, kRetryTextPos.y,
		"リトライ", kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kGameover)]);
	DrawStringFToHandle(kStageTextPos.x, kStageTextPos.y,
		"ステージ選択にもどる", kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kGameover)]);
	DrawStringFToHandle(kTitleTextPos.x, kTitleTextPos.y,
		"タイトルにもどる", kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kGameover)]);

	DrawFade();	// フェードインアウト描画

#ifdef _DEBUG	// デバッグ表示
	// 現在のシーン
	DrawString(0, 0, "ゲームオーバー画面", 0xffffff);
	// 中心線
	//DrawLine(Game::kScreenWidth * 0.5, 0, Game::kScreenWidth * 0.5, Game::kScreenHeight, 0x0000ff);
#endif
}