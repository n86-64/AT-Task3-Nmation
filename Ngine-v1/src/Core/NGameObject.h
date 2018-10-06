// File - GameObject.h
// Discription - Represents an Object within the Game Scene.

#pragma once

#include "Helpers/NMaths.h"

class NRenderer;

class NGameObject 
{
public:
	NGameObject() {};

	// Consider adding a pre-tick and post tick.
	// TODO - Implimenting Timing values.
	// Updates the engine each frame.
	virtual void Update() = 0;

	// Renders the object on screen.
	// TODO - Have renderer register components then draw.
	virtual void Render(NRenderer* renderer) = 0;

private:
	
	/* 3D Object Transforms. (Allows us to render these objects.) */
	NMath::Vector3  position; // The position of the object in 3D space. 
	NMath::Vector3	rotation; // The rotation of the object (represented via quaternions.)
	NMath::Vector3  scale; // The scale of the object in 3D space. (By Default Set to 1)
};