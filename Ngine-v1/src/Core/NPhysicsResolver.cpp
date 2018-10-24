#include "NGameObject.h"
#include "NPhysicsResolver.h"

void NPhysicsResolver::RegisterObject(NPhysicsComponent* newComp)
{
	physics_objects.push_back(newComp);
}

void NPhysicsResolver::tickPhysics(GameStateData gameData)
{
	// Here we will update the position of the object.
	for (NPhysicsComponent* object : physics_objects) 
	{
		// Apply global constants.
		if (!object->isKinematic()) 
		{
			object->getGameObject()->setPosition((object->getGameObject()->getPosition() + (gravity * gameData.timeData->getDeltaTimeInSeconds())));
		}

		testCollision(object);
	}
}

void NPhysicsResolver::testCollision(NPhysicsComponent* a)
{
	for (NPhysicsComponent* object : physics_objects) 
	{
		if ((a != object))
		{
			if (isObjectColliding(a, object)) 
			{
				// Trigger collision event.
				a->onCollision(object);
				object->onCollision(a);
			}
		}
	}
}

bool NPhysicsResolver::isObjectColliding(NPhysicsComponent* a, NPhysicsComponent* b)
{
	NColliderAABB& aCol = a->getCollider();
	NColliderAABB& bCol = b->getCollider();

	NMath::Vector3 aMax = a->getGameObject()->getPosition() + aCol.getColliderDimenstions();
	NMath::Vector3 aMin = a->getGameObject()->getPosition() - aCol.getColliderDimenstions();

	NMath::Vector3 bMax = b->getGameObject()->getPosition() + bCol.getColliderDimenstions();
	NMath::Vector3 bMin = b->getGameObject()->getPosition() - bCol.getColliderDimenstions();

	if (aMax.x() > bMin.x() && aMin.x() < bMax.x()) 
	{
		if (aMax.y() > bMin.y() && aMin.y() < bMax.y())
		{
			if (aMax.z() > bMin.z() && aMin.z() < bMax.z())
			{
				return true;
			}
		}
	}

	return false;
}
