#pragma once
#include "SceneBase.h"

/// <summary>
/// デバッグ用シーン
/// </summary>
class SceneDebug : public SceneBase
{
public:
	SceneDebug();
	virtual ~SceneDebug() {};
	virtual void Init() {};
	virtual std::shared_ptr<SceneBase> Update(Input& input);
	virtual void Draw();

private:
	// シーンの種類
	enum SelectScene
	{
		kTitle,			// タイトル
		kStageSelect,	// ステージ選択
		kOption,		// オプション
		kStage1,		// ステージ1
		kStage2,		// ステージ2
		kClear,			// クリア
		kGameover,		// ゲームオーバー
		kSelectNum		// シーンの数
	};
};

