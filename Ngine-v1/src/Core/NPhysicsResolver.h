// File - NPhysicsResolver
// Description - Contains all for the logic for testing collisions.

#pragma once


#include <vector>
#include "NPhysicsComponent.h"

class NPhysicsResolver 
{
public:
	NPhysicsResolver() = default;
	~NPhysicsResolver() = default;

	void RegisterObject(NPhysicsComponent* newComp);

	// Update the physics in the game world.
	void tickPhysics();

private:
	std::vector<NPhysicsComponent*>      physics_objects;

	// The gravity in cm/s
	NMath::Vector3						 gravity = NMath::Vector3(0.0f, -980.0f, 0.0f);
};