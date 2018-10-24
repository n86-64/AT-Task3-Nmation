// File - Camera.h
// Description - A Camera object which is used to project to a 3D environment.

#pragma once

#include "NGameObject.h"

class NCamera : public NGameObject 
{
public:
	NCamera();

	void Update(GameStateData& input) override;
	void Render(NRenderer* renderer) override;

	float getCameraNearZ();
	float getCameraFarZ();
	float getCameraFov();

	void setCameraBoundsZ(float nearPos, float farPos);

	NMath::Vector3   getCameraLookAt(); 
	void			 setCameraLookAt(NGameObject* target);
	void			 clearCameraTarget();

private:
	float			 movementvelocity;

	NMath::Vector3    cameraViewport;

	// LookAt TODO
	// Set lookAt to be forward of the camera by default unless a gameobject target is assigned.
	// In these cases lookat should be set to that objects position.
	// Camera rotations should also be applied to these objects.
	NMath::Vector3	  cameraForward = NMath::Vector3(0.0f, 0.0f, 1.0f); // TODO - Replace with calculated forward vector instead of hardcoded position. 
	
	// The position the camera should be looking at.
	NGameObject*      cameraTarget = nullptr;

	float nearZ = 0.1f, farZ = 110.0f;  // Camera bounding volumes
	float fov = 90.0f; // The field of view in degrees. 

	float testX = 0.0f;
};