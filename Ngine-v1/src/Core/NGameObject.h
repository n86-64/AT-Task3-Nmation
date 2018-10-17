// File - GameObject.h
// Discription - Represents an Object within the Game Scene.

#pragma once

#include <vector>

#include "Helpers/NMaths.h"

#include "Core/NDataStructures.h"
#include "Core/InputHandler.h"
#include "Core/time.h"

#include "NComponent.h"

class NRenderer;

class NGameObject 
{
public:
	NGameObject() {};

	// Consider adding a pre-tick and post tick.
	// TODO - Implimenting Timing values.
	// Updates the engine each frame.
	virtual void Update(GameStateData& gameData);

	// Renders the object on screen.
	// TODO - Have renderer register components then draw.
	virtual void Render(NRenderer* renderer);

	NMath::Vector3  getPosition();
	void		    setPosition(NMath::Vector3 newPos);

	// Add a component to the list.
	void addComponent(NComponent* newComp);

	NMath::Vector3   getTransformValue();

protected:
	std::vector<std::unique_ptr<NComponent>> objectComponents;

	/* 3D Object Transforms. (Allows us to render these objects.) */
	NMath::Vector3  position; // The position of the object in 3D space. 
	NMath::Vector3	rotation; // The rotation of the object (represented via quaternions.)
	NMath::Vector3  scale = NMath::Vector3(1.0f, 1.0f, 1.0f); // The scale of the object in 3D space. (By Default Set to 1)
};