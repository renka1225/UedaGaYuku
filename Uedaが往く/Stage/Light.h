#pragma once
#include "DxLib.h"
#include "Input.h"

class Light
{
public:
	void Create(); // ���C�g�쐬
	void Delete(); // ���C�g�폜
	void Update();	// ���C�g�X�V

private:
	int m_spotLight; // �X�|�b�g���C�g
};