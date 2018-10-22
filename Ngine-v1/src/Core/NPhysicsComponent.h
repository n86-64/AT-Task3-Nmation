// File - NPhysicsComponent.h
// Description - A component used to perform physics calculations.

#pragma once

#include <functional>

#include "NComponent.h"
#include "NColliderAABB.h"

// TODO - Consider changing the name of the object.
class NPhysicsComponent  : public NComponent
{
public:
	NPhysicsComponent() = default;
	~NPhysicsComponent() = default;

	bool isObjectColliding(NPhysicsComponent&  componentToTest);

	// Inherited via NComponent
	virtual void Construct(EngineStateData engineState, NConstructorValues constructorData) override;
	virtual void Update() override;
	virtual void Render(NRenderer* renderer) override;

	// Function called by the 
	void onCollision(NPhysicsComponent* comp);

	bool isKinematic() { return is_kinematic; }

	std::function<void(NPhysicsComponent*)> getCollisionEventHandle();
	void registerCollisionEvent(std::function<void(NPhysicsComponent*)> col_function);

	NColliderAABB& getCollider() { return collider; };

private:
	NColliderAABB		collider;

	// Function ptr that is called to perform testing.
	std::function<void(NPhysicsComponent*)>   function_ptr = nullptr;

private:
	// The Mass of the object in 3D Space.
	float			mass = 1.0f;
	bool			is_kinematic = true;
};