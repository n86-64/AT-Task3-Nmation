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
	// Apply the speed changes here.

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
