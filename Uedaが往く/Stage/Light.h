#pragma once
#include "DxLib.h"
#include "Input.h"

class Light
{
public:
	void Create(); // ライト作成
	void Delete(); // ライト削除
	void Update();	// ライト更新

private:
	int m_spotLight; // スポットライト
};