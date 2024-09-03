#include "Light.h"

void Light::SetLight()
{
	// ���C�g�ʒu����
	SetLightPosition(kDirLightPos);
	SetLightDirection(kDirLightDir);

	printfDx("X:%f,Y:%f,Z:%f", GetLightPosition().x, GetLightPosition().y, GetLightPosition().z);

	// �|�C���g���C�g�쐬
	//int pointLight = CreatePointLightHandle(kPointLightPos, kPointLightRange, kPointLightAtten0, kPointLightAtten1, kPointLightAtten2);

	// �X�|�b�g���C�g�쐬
	m_spotLight = CreateSpotLightHandle(kSpotLightPos, kSpotLightDir, kSpotLightOutAngle, kSpotLightInAngle,
		kSpotLightRange, kSpotLighAtten0, kSpotLighAtten1, kSpotLighAtten2);
}
