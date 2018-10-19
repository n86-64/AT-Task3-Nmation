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

private:

	std::vector<NPhysicsComponent*>      physics_resolver;
};