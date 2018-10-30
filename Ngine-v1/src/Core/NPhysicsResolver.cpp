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
			object->incrementAcceleration(gravity);
		//	object->getGameObject()->setPosition((object->getGameObject()->getPosition() + (gravity * gameData.timeData->getDeltaTimeInSeconds())));
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
				// Here we will perform the responce. Adding forces etc.
				// Trigger collision event.
    			if (!a->isKinematic()) 
				{
					resolveCollision(a, object);
				}

				a->onCollision(object);
				object->onCollision(a);
			}
		}
	}
}

bool NPhysicsResolver::isObjectColliding(NPhysicsComponent* a, NPhysicsComponent* b)
{
	a->getOBBCollider().isObjectColliding(a, b);


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

void NPhysicsResolver::resolveCollision(NPhysicsComponent* a, NPhysicsComponent* b)
{
	NMath::Vector3 collisionNormal;

	NMath::Vector3  aColliderDim = a->getCollider().getColliderDimenstions() / 2;
	NMath::Vector3  bColliderDim = b->getCollider().getColliderDimenstions() / 2;

	collisionNormal = ((a->getGameObject()->getPosition() - (b->getGameObject()->getPosition()))) - bColliderDim - aColliderDim;
	// collisionNormal = NMath::Vector3(0.0f, 1.0f, 0.0f);

	//a->getGameObject()->setPosition(a->getGameObject()->getPosition() + (NMath::Vector3(DirectX::XMVector3Normalize(collisionNormal.getRawVector()))));
	a->incrementVelocity((a->getAcceleration() * a->getMass()) * (collisionNormal));
	//a->incrementVelocity(a->getVelocity() * (collisionNormal));
}
