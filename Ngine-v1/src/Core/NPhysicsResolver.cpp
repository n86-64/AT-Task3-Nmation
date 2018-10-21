#include "NPhysicsResolver.h"

void NPhysicsResolver::RegisterObject(NPhysicsComponent* newComp)
{
	physics_objects.push_back(newComp);
}

void NPhysicsResolver::tickPhysics()
{
	// Here we will update the position of the object.

}
