#include "DxLib.h"
#include "DebugDraw.h"

// �萔
namespace
{
	constexpr int kBodyColor = 0x0000ff; // �S�g�̓����蔻��̐F
	constexpr int kAimColor = 0xff00ff;  // �r�̓����蔻��̐F
	constexpr int kLegColor = 0xffff00;  // �r�̓����蔻��̐F
}


/// <summary>
/// �v���C���[�̏���`��
/// </summary>
/// <param name="pos">���W</param>
/// <param name="hp">���݂�HP</param>
/// <param name="currentState">���݂̏��</param>
/// <param name="attackTime">�U������</param>
void DebugDraw::DrawPlayerInfo(VECTOR pos, float hp, int currentState, int attackTime)
{
	DrawFormatString(0, 20, 0xffffff, "�v���C���[���W(%0.2f,%0.2f,%0.2f)", pos.x, pos.y, pos.z);
	DrawFormatString(0, 40, 0xffffff, "�v���C���[HP:%0.2f", hp);
	DrawFormatString(0, 60, 0xffffff, "�v���C���[���:%d", currentState);
	DrawFormatString(0, 80, 0xffffff, "�v���C���[�U������:%d", attackTime);
}


/// <summary>
/// �G�̏���`��
/// </summary>
/// <param name="pos">���W</param>
/// <param name="hp">���݂�HP</param>
/// <param name="currentState">���݂̏��</param>
/// <param name="attackTime">�U������</param>
void DebugDraw::DrawEnemyInfo(VECTOR pos, float hp, int currentState, int attackTime)
{
	DrawFormatString(0, 100, 0xffffff, "�G���W(%0.2f,%0.2f,%0.2f)", pos.x, pos.y, pos.z);
	DrawFormatString(0, 120, 0xffffff, "�Ghp:%0.2f", hp);
	DrawFormatString(0, 140, 0xffffff, "�G���:%d", currentState);
	DrawFormatString(0, 160, 0xffffff, "�G�U������:%d", attackTime);
}


/// <summary>
/// �S�g�̓����蔻���`��
/// </summary>
/// <param name="startPos">�J�n�ʒu</param>
/// <param name="endPos">�I���ʒu</param>
/// <param name="r">���a</param>
void DebugDraw::DrawBodyCol(VECTOR startPos, VECTOR endPos, float r)
{
	DrawCapsule3D(startPos, endPos, r, 1, kBodyColor, 0xffffff, false);
}


/// <summary>
/// �r�̓����蔻���`��
/// </summary>
/// <param name="startPos">�J�n�ʒu</param>
/// <param name="endPos">�I���ʒu</param>
/// <param name="r">���a</param>
void DebugDraw::DrawAimCol(VECTOR startPos, VECTOR endPos, float r)
{
	DrawCapsule3D(startPos, endPos, r, 1, kAimColor, 0xffffff, false);
}


/// <summary>
/// �r�̓����蔻���`��
/// </summary>
/// <param name="startPos">�J�n�ʒu</param>
/// <param name="endPos">�I���ʒu</param>
/// <param name="r">���a</param>
void DebugDraw::DrawLegCol(VECTOR startPos, VECTOR endPos, float r)
{
	DrawCapsule3D(startPos, endPos, r, 1, kLegColor, 0xffffff, false);
}
