#include "Light.h"

// 定数
namespace
{
	/*スポットライト*/
	constexpr float kSpotLightOutAngle = 0.0f;					 // スポットライトコーンの外側の角度
	constexpr float kSpotLightInAngle = 90.0f;					 // スポットライトコーンの内側の角度
	constexpr float kSpotLightRange = 100.0f;					 // 有効距離
	constexpr float kSpotLighAtten0 = 0.0f;						 // 距離減衰パラメータ0
	constexpr float kSpotLighAtten1 = 0.001f;					 // 距離減衰パラメータ1
	constexpr float kSpotLighAtten2 = 0.0f;						 // 距離減衰パラメータ2
}


/// <summary>
/// ライト作成
/// </summary>
void Light::Create()
{
	// スポットライト作成
	m_spotLight = CreateSpotLightHandle(GetCameraPosition(), GetCameraTarget(), kSpotLightOutAngle, kSpotLightInAngle,
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
	SetLightPositionHandle(m_spotLight, GetCameraPosition());
}
