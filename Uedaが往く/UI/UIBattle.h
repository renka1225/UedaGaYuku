#pragma once
#include "UI.h"

/// <summary>
/// バトル中に表示するUIを管理する
/// </summary>
class UIBattle : public UI
{
public:
	UIBattle();
	UIBattle(float maxHp);
	virtual ~UIBattle();
	void UpdateHpBar();				// HP表示を更新する
	void SetDamageTimer();			// ダメージを受けた際にタイマーをセットする
	void OnDamage(float damage);	// 受けたダメージ量を計算する
	void DrawStartProduction(int time, int matchNum, int maxMatch); // スタート時の演出を表示
	void DrawPlayerHP(float currentHp);								// プレイヤーのHPバーを表示
	void DrawPlayerGauge(float currentGauge, float MaxGauge);		// プレイヤーのゲージバーを表示
	void DrawEnemyHp(float currentHp);								// 敵のHPバーを表示
	void DrawSilhouette(int charType);								// シルエットを表示
	void DrawSpecialAttack();										// 必殺技のテキスト表示
	void DrawOperation();											// 操作説明を表示
	void DrawTutoButtonText();										// チュートリアル画面のボタン表示

private:
	float m_decreaseHp;				// ダメージを受けた後のHP
	float m_currentHp;				// 現在のHP
	float m_damage;					// 受けたダメージ量
	float m_maxHp;					// 最大HP
	int m_intervalTime;				// HPバーが減少するまでの時間
	int m_gaugeBarHandle;			// ゲージバーの画像
	int m_silhouetteHandle;			// キャラクターのシルエット画像
	int m_fightTextHandle;			// "Fight"のテキスト画像
	int m_numTextHandle;			// 数字の画像
	std::vector<int> m_handle;		// ハンドル

	// 画像の種類
	enum HandleKind
	{
		kGaugeBar,	 // ゲージバー
		kSilhouette, // キャラクターのシルエット
		kFightText,	 // "Fight!"のテキスト
		kNumText,	 // 数字
		kHandleNum	 // ハンドルの種類
	};

	// 操作説明で表示する順番
	enum OperationOrder
	{
		kMove,			// 移動
		kCameraMove,	// カメラ移動
		kPunch,			// パンチ
		kKick,			// キック
		kAvoid,			// 回避
		kGuard,			// ガード
		kRockon,		// ロックオン
		kPause,			// ポーズ
	};
};
