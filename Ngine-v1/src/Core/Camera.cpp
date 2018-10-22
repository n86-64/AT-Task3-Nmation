#include "Camera.h"

NCamera::NCamera()
{
	position = NMath::Vector3(0.0f, 1.0f, -5.0f);
}

void NCamera::Update(GameStateData& gameData)
{

}

void NCamera::Render(NRenderer* renderer)
{
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
		return cameraTarget->getPosition();
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
