#include "Camera.h"

NCamera::NCamera()
{
	position = NMath::Vector3(0.0f, 1.0f, -5.0f);
}

void NCamera::Update(NInputHandler* input)
{
	if (input->getKeyDown(NKeyboardKeys::KEY_A)) 
	{
		testX += 0.1f;
		position.setX(position.x() + sin(testX));
	}
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
