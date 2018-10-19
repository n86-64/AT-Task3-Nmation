#include "NPhysicsResolver.h"

void NPhysicsResolver::RegisterObject(NPhysicsComponent* newComp)
{
	physics_resolver.push_back(newComp);
}
