#include "DxLib.h"
#include "Player.h"
#include "Stage.h"
#include "UIBattle.h"
#include "EffectManager.h"
#include "LoadData.h"
#include "DebugDraw.h"
#include "EnemyChef.h"

// 定数
namespace
{
	// 敵情報
	const char* const kfileName = "data/Model/Chara/Chef.mv1";	// 敵のファイル名
	constexpr float kScale = 0.3f;								// 拡大率
	constexpr int kIntervalTime = 120;							// 状態を更新するまでの時間
}


/// <summary>
/// コンストラクタ
/// </summary>
EnemyChef::EnemyChef()
{
	// キャラクター情報を読み込む
	m_pLoadData = std::make_shared<LoadData>(*this, static_cast<int>(CharaType::kEnemyChef));
	m_enemyType = static_cast<int>(CharaType::kEnemyChef);
	m_pUIBattle = std::make_shared<UIBattle>(m_status.maxHp, m_enemyType);
	m_hp = m_status.maxHp;
	m_moveSpeed = m_status.maxMoveSpeed;
	m_modelHandle = MV1LoadModel(kfileName);
	MV1SetScale(m_modelHandle, VGet(kScale, kScale, kScale));
}


/// <summary>
/// デストラクタ
/// </summary>
EnemyChef::~EnemyChef()
{
	MV1DeleteModel(m_modelHandle);
}


/// <summary>
/// 初期化
/// </summary>
/// <param name="pos">初期位置</param>
void EnemyChef::Init(std::shared_ptr<EffectManager> pEffect, VECTOR pos)
{
	m_pos = pos;
	m_pEffect = pEffect;
	MV1SetPosition(m_modelHandle, m_pos);
	m_pEffect->Init();	// エフェクトの初期化
}


/// <summary>
/// 更新
/// </summary>
/// <param name="player">プレイヤー参照</param>
/// <param name="stage">ステージ参照</param>
void EnemyChef::Update(Player& player, Stage& stage, SceneStageBase& sceneStage)
{
	// 移動パラメータを設定する
	VECTOR	upMoveVec;		// 上ボタンを入力をしたときのプレイヤーの移動方向ベクトル
	VECTOR	leftMoveVec;	// 左ボタンを入力をしたときのプレイヤーの移動方向ベクトル
	VECTOR	moveVec;		// このフレームの移動ベクトル

	// エネミーの状態を更新
	CharacterBase::State prevState = m_currentState;

	// 敵の位置からプレイヤー位置までのベクトルを求める
	m_eToPDirVec = VSub(player.GetPos(), m_pos);

	// 状態を更新する
	m_currentState = UpdateState(player, sceneStage, upMoveVec, leftMoveVec, moveVec);

	// プレイヤーとの当たり判定をチェックする
	player.CheckHitEnemyCol(*this, VGet(m_pos.x, m_pos.y + m_colInfo.bodyHeight, m_pos.z), m_pos, m_colInfo.bodyRadius);

	UpdateAnimState(prevState);		// アニメーション状態を更新
	UpdateAngle();					// 角度を更新
	UpdateGuard();					// ガード状態を更新
	Move(moveVec, player, stage);	// 移動ベクトルを元にエネミーを移動させる
	UpdateAnim();					// アニメーション処理の更新
	UpdateCol();					// 当たり判定位置更新
	UpdatePosLog();					// 位置ログを更新
	m_pUIBattle->UpdateHpBar();		// HPバーの更新
	m_pEffect->Update();			// エフェクト更新
}


/// <summary>
/// 描画
/// </summary>
void EnemyChef::Draw()
{
	MV1DrawModel(m_modelHandle);
	m_pEffect->Draw();					// エフェクト描画

	// 回避中は残像を表示する
	if (m_currentState == State::kAvoid)
	{
		DrawAfterImage();
	}

#ifdef _DEBUG
	DebugDraw debug;
	debug.DrawEnemyInfo(m_pos, m_hp, static_cast<int>(m_currentState));
	// 当たり判定描画
	debug.DrawBodyCol(m_col.bodyTopPos, m_col.bodyBottomPos, m_colInfo.bodyRadius); // 全身
	debug.DrawAimCol(m_col.armStartPos, m_col.armEndPos, m_colInfo.aimRadius);		// 腕
	debug.DrawLegCol(m_col.legStartPos, m_col.legEndPos, m_colInfo.legRadius);		// 脚
#endif
}


/// <summary>
/// UI表示
/// </summary>
void EnemyChef::DrawUi()
{
	m_pUIBattle->DrawEnemySilhouette(static_cast<int>(CharacterBase::CharaType::kEnemyChef)); // シルエット描画
	m_pUIBattle->DrawEnemyName(static_cast<int>(CharacterBase::CharaType::kEnemyChef));		  // 敵の名前ゲージ表示
	m_pUIBattle->DrawEnemyHp(m_hp);		// HPゲージを表示
}
