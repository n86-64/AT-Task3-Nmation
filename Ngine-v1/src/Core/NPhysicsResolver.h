// File - NPhysicsResolver
// Description - Contains all for the logic for testing collisions.

#pragma once


#include <vector>
#include "NSceneGraph.h"

class NPhysicsResolver 
{
public:
	NPhysicsResolver() = default;
	~NPhysicsResolver() = default;

	void RegisterObject(NPhysicsComponent* newComp);

	// Update the physics in the game world.
	void tickPhysics(GameStateData gameData);

private:
	void testCollision(NPhysicsComponent* a);

	bool isObjectColliding(NPhysicsComponent* a, NPhysicsComponent* b);

	void resolveCollision(NPhysicsComponent* a, NPhysicsComponent* b);

	std::vector<NPhysicsComponent*>      physics_objects;

	NSceneGraph							 sceneOctree; // Used for collision testing.

	// The gravity in cm/s
	NMath::Vector3						 gravity = NMath::Vector3(-0.0f, -0.981f, -0.0f);
};