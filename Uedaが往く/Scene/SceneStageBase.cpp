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
	const VECTOR kPlayerInitPos = VGet(2600.0f, 69.0f, 4240.0f);  // プレイヤーの初期位置
	const VECTOR kEnemyInitPos = VGet(2660, 69.0f, 4280.0f);	  // 敵の初期位置
	constexpr int kChangeColorTime = 220;						  // 画面の表示を変更する時間
	constexpr int kClearStagingTime = 240;						  // クリア演出の時間
	constexpr int kNextBattleTime = 300;						  // 次の試合が始まるまでの時間
	constexpr int kBattleEndSoundTime = 60;						  // コングのSEを鳴らす時間
	constexpr int kClearBackColor = 0x0f2699;					  // クリア時の背景色
	constexpr int kMULAPal = 240;								  // 乗算ブレンド値
	constexpr int kAddPal = 80;									  // 加算ブレンド値
	
	/*影*/
	constexpr int kShadowMapSize = 4096;							  // 作成するシャドウマップのサイズ
	const VECTOR kShadowAreaMinPos = VGet(2200.0f, 65.0f, 3800.0f);	  // シャドウマップに描画する最小範囲
	const VECTOR kShadowAreaMaxPos = VGet(3000.0f, 100.0f, 5000.0f);  // シャドウマップに描画する最大範囲

	constexpr int kStartFadeAlpha = 255; // スタート時のフェード値
	constexpr int kFadeFrame = 8;		 // フェード変化量
}


/// <summary>
/// コンストラクタ
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
	// シャドウマップが想定するライトの方向をセット
	SetShadowMapLightDirection(m_shadowMap, GetLightPosition());
	// シャドウマップに描画する範囲を設定
	SetShadowMapDrawArea(m_shadowMap, kShadowAreaMinPos, kShadowAreaMaxPos);

	m_fadeAlpha = kStartFadeAlpha;
	m_pEffect = std::make_shared<EffectManager>();
	m_pLight = std::make_shared<Light>();
	m_clearBackHandle = LoadGraph("data/UI/clearBack.png");
}


/// <summary>
/// 引数つきコンストラクタ
/// </summary>
/// <param name="pPlayer">プレイヤー参照</param>
/// <param name="pCamera">カメラ参照</param>
/// <param name="pStage">ステージ参照</param>
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
/// デストラクタ
/// </summary>
SceneStageBase::~SceneStageBase()
{
	//m_pLight->Delete();
	DeleteShadowMap(m_shadowMap); // シャドウマップの削除
	DeleteGraph(m_clearBackHandle);
}


/// <summary>
/// 初期化
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
/// 描画
/// </summary>
void SceneStageBase::Draw()
{
	ShadowMap_DrawSetup(m_shadowMap); // シャドウマップへの描画の準備
	m_pStage->Draw();	 // ステージ描画
	m_pPlayer->Draw();	 // プレイヤー描画
	m_pEnemy->Draw();	 // 敵描画
	ShadowMap_DrawEnd(); // シャドウマップへの描画を終了

	SetUseShadowMap(0, m_shadowMap); // 描画に使用するシャドウマップを設定
	m_pStage->Draw();	 // ステージ描画
	m_pPlayer->Draw();	 // プレイヤー描画
	m_pEnemy->Draw();	 // 敵描画
	SetUseShadowMap(0, -1); // 描画に使用するシャドウマップの設定を解除

	m_pEnemy->DrawUi();			  // 敵のUI描画
	m_pUIBattle->DrawOperation(); // 操作説明を表示

	// クリア時画面の色味を変える
	if (m_clearStagingTime < kClearStagingTime && m_clearStagingTime >= 0)
	{
		SetDrawBlendMode(DX_BLENDMODE_MULA, kMULAPal);
		DrawGraph(0, 0, m_clearBackHandle, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		SetDrawBlendMode(DX_BLENDMODE_ADD, kAddPal);
		DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, kClearBackColor, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	DrawFade();	// フェードインアウト描画

#ifdef _DEBUG
	//TestDrawShadowMap(m_shadowMap, 0, 0, 320, 240); // 画面左上にシャドウマップをテスト描画
	DrawFormatString(0, 140, 0xffffff, "経過時間:%d", m_elapsedTime); // 経過時間描画
	DrawFormatString(0, 180, 0xffffff, "カメラ位置(X:%.2f, Y:%.2f, Z:%.2f)", GetCameraPosition().x, GetCameraPosition().y, GetCameraPosition().z);
	m_pLight->Draw(); // ライト位置描画
#endif
}


/// <summary>
/// クリア演出を行う
/// </summary>
void SceneStageBase::ClearStaging()
{
	// SEを鳴らす
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

	// クリア演出をリセット
	m_clearStagingTime = 0;
	StopSoundMem(Sound::m_seHandle[static_cast<int>(Sound::SeKind::kClearCheers)]);
}


/// <summary>
/// 敵を倒して次試合が始まる前の処理
/// </summary>
void SceneStageBase::UpdateNextBattle()
{
	m_nextBattleTime = kNextBattleTime;
	m_clearStagingTime = kClearStagingTime;
	m_pUIBattle->ResetStartProduction();
	m_pUIBattle->SetEnemyKind(m_pEnemy->GetEnemyType());
	// プレイヤーの位置、カメラ位置を最初の状態に戻す
	m_pPlayer->Recovery();
	Init();

	FadeIn(kFadeFrame); // フェードイン
}