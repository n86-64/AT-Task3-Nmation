#include "NGameObject.h"
#include "NPhysicsComponent.h"

bool NPhysicsComponent::isObjectColliding(NPhysicsComponent& componentToTest)
{
	// Here we will perform collision tests.
	return false;
}

void NPhysicsComponent::Construct(EngineStateData engineState, NConstructorValues constructorData)
{
	return;
}

void NPhysicsComponent::Update(GameStateData& gameData)
{
	// Apply the speed changes here.
	velocity = velocity + (acceleration * gameData.timeData->getDeltaTimeInSeconds());
	this->getGameObject()->setPosition(this->getGameObject()->getPosition() + (velocity * gameData.timeData->getDeltaTimeInSeconds()));
	acceleration = NMath::Vector3(0.0f, 0.0f, 0.0f);

	return;
}

void NPhysicsComponent::Render(NRenderer* renderer)
{
	return;
}

void NPhysicsComponent::onCollision(NPhysicsComponent* comp)
{
	if (function_ptr) 
	{
		function_ptr(comp);
	}

	return;
}

std::function<void(NPhysicsComponent*)> NPhysicsComponent::getCollisionEventHandle()
{
	return function_ptr;
}

void NPhysicsComponent::registerCollisionEvent(std::function<void(NPhysicsComponent*)> colFunction)
{
	function_ptr = colFunction;
}

void NPhysicsComponent::incrementAcceleration(NMath::Vector3 accelerate)
{
	acceleration = acceleration + accelerate;
}

NMath::Vector3 NPhysicsComponent::getAcceleration() const
{
	return acceleration;
}

void NPhysicsComponent::incrementVelocity(NMath::Vector3 newVel)
{
	velocity = velocity + newVel;
}
