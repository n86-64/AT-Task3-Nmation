// File - Camera.h
// Description - A Camera object which is used to project to a 3D environment.

#pragma once

#include "NGameObject.h"

class NCamera : public NGameObject 
{
public:
	NCamera();

	void Update() override;
	void Render(NRenderer* renderer) override;

	float getCameraNearZ();
	float getCameraFarZ();

	void setCameraBoundsZ(float nearPos, float farPos);

private:
	NMath::Vector3    cameraViewport;

	float nearZ = 0.1f, farZ = 110.0f;  // Camera bounding volumes
	float fov;
};