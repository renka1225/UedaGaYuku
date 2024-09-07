#pragma once

/// <summary>
/// デバッグ情報を表示
/// </summary>
class DebugDraw
{
public:
	DebugDraw() {};
	~DebugDraw() {};
	void DrawPlayerInfo(VECTOR pos, float hp, int currentState, int attackTime); // プレイヤーの情報を描画
	void DrawEnemyInfo(VECTOR pos, float hp, int currentState, int attackTime);	 // 敵の情報を描画
	void DrawBodyCol(VECTOR startPos, VECTOR endPos, float r);					 // 全身の当たり判定を描画
	void DrawAimCol(VECTOR startPos, VECTOR endPos, float r);					 // 腕の当たり判定を描画
	void DrawLegCol(VECTOR startPos, VECTOR endPos, float r);					 // 脚の当たり判定を描画
};

