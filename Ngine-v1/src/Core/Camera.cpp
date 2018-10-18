#include "Camera.h"

NCamera::NCamera()
{
	position = NMath::Vector3(0.0f, 1.0f, -5.0f);
}

void NCamera::Update(GameStateData& gameData)
{
	float speed = 20.0f * (gameData.timeData->getDeltaTime() / 1000.0f);

	position.setZ(position.z() + (speed * gameData.input->getKeyDown(NKeyboardKeys::KEY_W)));
	position.setZ(position.z() - (speed * gameData.input->getKeyDown(NKeyboardKeys::KEY_S)));

	position.setX(position.x() + (speed * gameData.input->getKeyDown(NKeyboardKeys::KEY_D)));
	position.setX(position.x() - (speed * gameData.input->getKeyDown(NKeyboardKeys::KEY_A)));
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
