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

void NPhysicsComponent::Update()
{
	return;
}

void NPhysicsComponent::Render(NRenderer* renderer)
{
	return;
}

void NPhysicsComponent::onCollision()
{

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
