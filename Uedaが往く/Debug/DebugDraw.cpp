#include "DxLib.h"
#include "DebugDraw.h"

// 定数
namespace
{
	constexpr int kBodyColor = 0x0000ff; // 全身の当たり判定の色
	constexpr int kAimColor = 0xff00ff;  // 腕の当たり判定の色
	constexpr int kLegColor = 0xffff00;  // 脚の当たり判定の色
}


/// <summary>
/// プレイヤーの情報を描画
/// </summary>
/// <param name="pos">座標</param>
/// <param name="hp">現在のHP</param>
/// <param name="currentState">現在の状態</param>
void DebugDraw::DrawPlayerInfo(VECTOR pos, float hp, int currentState)
{
	DrawFormatString(0, 20, 0xffffff, "プレイヤー座標(%0.2f,%0.2f,%0.2f)", pos.x, pos.y, pos.z);
	DrawFormatString(0, 40, 0xffffff, "hp:%0.2f", hp);
	DrawFormatString(0, 60, 0xffffff, "状態:%d", currentState);
}


/// <summary>
/// 敵の情報を描画
/// </summary>
/// <param name="pos">座標</param>
/// <param name="hp">現在のHP</param>
/// <param name="currentState">現在の状態</param>
void DebugDraw::DrawEnemyInfo(VECTOR pos, float hp, int currentState)
{
	DrawFormatString(0, 80, 0xffffff, "敵座標(%0.2f,%0.2f,%0.2f)", pos.x, pos.y, pos.z);
	DrawFormatString(0, 100, 0xffffff, "hp:%0.2f", hp);
	DrawFormatString(0, 120, 0xffffff, "状態:%d", currentState);
}


/// <summary>
/// 全身の当たり判定を描画
/// </summary>
/// <param name="startPos">開始位置</param>
/// <param name="endPos">終了位置</param>
/// <param name="r">半径</param>
void DebugDraw::DrawBodyCol(VECTOR startPos, VECTOR endPos, float r)
{
	DrawCapsule3D(startPos, endPos, r, 1, kBodyColor, 0xffffff, false);
}


/// <summary>
/// 腕の当たり判定を描画
/// </summary>
/// <param name="startPos">開始位置</param>
/// <param name="endPos">終了位置</param>
/// <param name="r">半径</param>
void DebugDraw::DrawAimCol(VECTOR startPos, VECTOR endPos, float r)
{
	DrawCapsule3D(startPos, endPos, r, 1, kAimColor, 0xffffff, false);
}


/// <summary>
/// 脚の当たり判定を描画
/// </summary>
/// <param name="startPos">開始位置</param>
/// <param name="endPos">終了位置</param>
/// <param name="r">半径</param>
void DebugDraw::DrawLegCol(VECTOR startPos, VECTOR endPos, float r)
{
	DrawCapsule3D(startPos, endPos, r, 1, kLegColor, 0xffffff, false);
}
