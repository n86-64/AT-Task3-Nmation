#include "Camera.h"

NCamera::NCamera()
{
	position = NMath::Vector3(0.0f, 1.0f, -5.0f);
}

void NCamera::Update(GameStateData& gameData)
{
	cameraForward = DirectX::XMVector3Transform(forward.getRawVector(), DirectX::XMMatrixRotationQuaternion(DirectX::XMQuaternionRotationRollPitchYawFromVector(rotation.getRawVector())));
	NGameObject::Update(gameData);
}

void NCamera::Render(NRenderer* renderer)
{
	NGameObject::Render(renderer);
	return;
}

float NCamera::getCameraNearZ()
{
	return nearZ;
}

float NCamera::getCameraFarZ()
{
	return farZ;
}

float NCamera::getCameraFov()
{
	return fov;
}

void NCamera::setCameraBoundsZ(float nearPos, float farPos)
{
	nearZ = nearPos;
	farZ = farPos;
}

NMath::Vector3 NCamera::getCameraLookAt()
{
	if (cameraTarget) 
	{
		return cameraTarget->getPosition() + cameraForward;
	}
	else 
	{
		return position + cameraForward;
	}
}

void NCamera::setCameraLookAt(NGameObject* target)
{
	cameraTarget = target;
}

void NCamera::clearCameraTarget()
{
	cameraTarget = nullptr;
}
