#include "Camera.h"

NCamera::NCamera()
{
	position = NMath::Vector3(0.0f, 1.0f, -5.0f);
}

void NCamera::Update(GameStateData& gameData)
{
	float speed = 1.0f * gameData.timeData->getDeltaTimeInSeconds();
	rotation = rotation + NMath::Vector3(0.0f, (speed * gameData.input->getKeyDown(NKeyboardKeys::KEY_X)) + (-speed * gameData.input->getKeyDown(NKeyboardKeys::KEY_Z)), 0.0f);

	realCameraForward = DirectX::XMVector3Transform(cameraForward.getRawVector(), DirectX::XMMatrixRotationQuaternion(DirectX::XMQuaternionRotationRollPitchYawFromVector(rotation.getRawVector())));
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
		return cameraTarget->getPosition();
	}
	else 
	{
		return position + realCameraForward;
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
