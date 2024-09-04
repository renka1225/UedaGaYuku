#include "DxLib.h"
#include "Player.h"
#include "Light.h"

// 定数
namespace
{
	/*スポットライト*/
	constexpr float kSpotLightOutAngle = 27.0f;	 // スポットライトの影響角度
	constexpr float kSpotLightInAngle = 18.0f;	 // スポットライトの影響が減衰を始める角度
	constexpr float kSpotLightRange = 147.0f;	 // 有効距離
	constexpr float kSpotLighAtten0 = 0.6f;		 // 距離減衰パラメータ0
	constexpr float kSpotLighAtten1 = 0.0f;		 // 距離減衰パラメータ1
	constexpr float kSpotLighAtten2 = 0.0f;		 // 距離減衰パラメータ2
	constexpr float kSpotLightDistance = 10.0f;  // ライトとプレイヤーの距離
	const VECTOR kSpotLightPos = VGet(-50.0f, -20.0f, -116.0f); // スポットライト位置
	const VECTOR kSpotLightDir = VGet(1.0f, 0.43f, 1.0f);		// スポットライト方向
}


/// <summary>
/// ライト作成
/// </summary>
void Light::Create(std::shared_ptr<Player> pPlayer)
{
	m_pPlayer = pPlayer;
	//m_dirLight = CreateDirLightHandle(VGet(0, 0, 0));

	m_spotLight = CreateSpotLightHandle(kSpotLightPos, kSpotLightDir, kSpotLightOutAngle, kSpotLightInAngle,
		kSpotLightRange, kSpotLighAtten0, kSpotLighAtten1, kSpotLighAtten2);
}


/// <summary>
/// ライト削除
/// </summary>
void Light::Delete()
{
	DeleteLightHandleAll();
}


/// <summary>
/// ライト更新
/// </summary>
void Light::Update()
{
	const VECTOR cameraPos = GetCameraPosition();  // カメラ位置取得
	const VECTOR playerPos = m_pPlayer->GetPos();  // プレイヤー位置取得
	VECTOR cameraToPlayerDir = VNorm(VSub(playerPos, cameraPos)); // カメラからプレイヤーまでのベクトルを計算する

	//SetLightDirectionHandle(m_dirLight, cameraToPlayerDir);
	SetLightPosition(VAdd(playerPos, kSpotLightPos));
}


#ifdef _DEBUG
/// <summary>
/// 描画
/// </summary>
void Light::Draw()
{
	DrawFormatString(0, 200, 0xffffff, "ライト位置(X:%.2f,Y:%.2f,Z;%.2f)", GetLightPositionHandle(m_spotLight).x, GetLightPositionHandle(m_spotLight).y, GetLightPositionHandle(m_spotLight).z);
	DrawFormatString(0, 220, 0xffffff, "ライト方向(X:%.2f,Y:%.2f,Z;%.2f)", GetLightDirectionHandle(m_spotLight).x, GetLightDirectionHandle(m_spotLight).y, GetLightDirectionHandle(m_spotLight).z);
}
#endif

