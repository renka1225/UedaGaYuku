#include "Light.h"

void Light::SetLight()
{
	// ライト位置調整
	SetLightPosition(kDirLightPos);
	SetLightDirection(kDirLightDir);

	printfDx("X:%f,Y:%f,Z:%f", GetLightPosition().x, GetLightPosition().y, GetLightPosition().z);

	// ポイントライト作成
	//int pointLight = CreatePointLightHandle(kPointLightPos, kPointLightRange, kPointLightAtten0, kPointLightAtten1, kPointLightAtten2);

	// スポットライト作成
	m_spotLight = CreateSpotLightHandle(kSpotLightPos, kSpotLightDir, kSpotLightOutAngle, kSpotLightInAngle,
		kSpotLightRange, kSpotLighAtten0, kSpotLighAtten1, kSpotLighAtten2);
}
