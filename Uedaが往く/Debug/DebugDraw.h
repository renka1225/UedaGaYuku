#pragma once

/// <summary>
/// �f�o�b�O����\��
/// </summary>
class DebugDraw
{
public:
	DebugDraw() {};
	~DebugDraw() {};
	void DrawPlayerInfo(VECTOR pos, float hp, int currentState, int attackTime); // �v���C���[�̏���`��
	void DrawEnemyInfo(VECTOR pos, float hp, int currentState, int attackTime);	 // �G�̏���`��
	void DrawBodyCol(VECTOR startPos, VECTOR endPos, float r);					 // �S�g�̓����蔻���`��
	void DrawAimCol(VECTOR startPos, VECTOR endPos, float r);					 // �r�̓����蔻���`��
	void DrawLegCol(VECTOR startPos, VECTOR endPos, float r);					 // �r�̓����蔻���`��
};

