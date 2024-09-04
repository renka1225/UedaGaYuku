#include "DxLib.h"
#include "Player.h"
#include "Light.h"

// 定数
namespace
{
	/*スポットライト*/
	constexpr float kSpotLightOutAngle = 45.0f;	 // スポットライトの影響角度
	constexpr float kSpotLightInAngle = 30.0f;	 // スポットライトの影響が減衰を始める角度
	constexpr float kSpotLightRange = 200.0f;	 // 有効距離
	constexpr float kSpotLighAtten0 = 0.0f;		 // 距離減衰パラメータ0
	constexpr float kSpotLighAtten1 = 0.015f;	 // 距離減衰パラメータ1
	constexpr float kSpotLighAtten2 = 0.0f;		 // 距離減衰パラメータ2
	//const VECTOR kSpotLightPos = VGet(-40.0f, 0.0f, -45.0f); // ライト位置
	constexpr float kSpotLightDistance = 10.0f;  // ライトとプレイヤーの距離
}


/// <summary>
/// ライト作成
/// </summary>
void Light::Create(std::shared_ptr<Player> pPlayer)
{
	m_pPlayer = pPlayer;
	const VECTOR cameraPos = GetCameraPosition();  // カメラ位置取得
	const VECTOR cameraTarget = GetCameraTarget(); // カメラ方向取得
	const VECTOR playerPos = m_pPlayer->GetPos();  // プレイヤー位置取得
	const VECTOR playerDir = m_pPlayer->GetDir();  // プレイヤーの方向取得
	VECTOR cameraToPlayerDir = VNorm(VSub(playerPos, cameraPos)); // カメラからプレイヤーまでのベクトルを計算する

	// スポットライト作成
	//m_spotLight = CreateSpotLightHandle(cameraPos, VAdd(playerPos, cameraToPlayerDir), kSpotLightOutAngle, kSpotLightInAngle,
		//kSpotLightRange, kSpotLighAtten0, kSpotLighAtten1, kSpotLighAtten2);

	m_spotLight = CreateSpotLightHandle(VAdd(playerPos, VScale(playerDir, kSpotLightDistance)), playerPos, kSpotLightOutAngle, kSpotLightInAngle,
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
	//const VECTOR cameraPos = GetCameraPosition();  // カメラ位置取得
	//const VECTOR playerPos = m_pPlayer->GetPos();  // プレイヤー位置取得
	//VECTOR cameraToPlayerDir = VNorm(VSub(playerPos, cameraPos)); // カメラからプレイヤーまでのベクトルを計算する

	//SetLightPositionHandle(m_spotLight, VAdd(playerPos, kSpotLightPos));

	const VECTOR playerPos = m_pPlayer->GetPos();   // プレイヤー位置取得
	const VECTOR playerDir = m_pPlayer->GetDir();  // プレイヤーの向き取得

	// ライトをプレイヤーの正面に配置
	VECTOR lightPos = VAdd(playerPos, VScale(playerDir, kSpotLightDistance));

	SetLightPositionHandle(m_spotLight, lightPos);
}


#ifdef _DEBUG
/// <summary>
/// 描画
/// </summary>
void Light::Draw()
{
	DrawFormatString(0, 200, 0xffffff, "ライト位置:(X:%.2f,Y:%.2f,Z;%.2f)", GetLightPositionHandle(m_spotLight).x, GetLightPositionHandle(m_spotLight).y, GetLightPositionHandle(m_spotLight).z);
}
#endif

