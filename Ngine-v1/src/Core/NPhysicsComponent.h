// File - NPhysicsComponent.h
// Description - A component used to perform physics calculations.

#pragma once

#include <functional>

#include "NComponent.h"
#include "NColliderAABB.h"
#include "NColliderOBB.h"

// TODO - Consider changing the name of the object.
class NPhysicsComponent  : public NComponent
{
public:
	NPhysicsComponent() = default;
	~NPhysicsComponent() = default;

	bool isObjectColliding(NPhysicsComponent&  componentToTest);

	// Inherited via NComponent
	virtual void Construct(EngineStateData engineState, NConstructorValues constructorData) override;
	virtual void Update(GameStateData& gameData) override;
	virtual void Render(NRenderer* renderer) override;

	// Function called by the 
	void onCollision(NPhysicsComponent* comp);

	bool isKinematic() { return is_kinematic; }
	void isKinematic(bool status) { is_kinematic = status; }

	float getMass() const { return mass; }
	void  setMass(float newMass) { mass = newMass; }

	std::function<void(NPhysicsComponent*)> getCollisionEventHandle();
	void registerCollisionEvent(std::function<void(NPhysicsComponent*)> col_function);

	NColliderAABB& getCollider() { return collider; };
	NColliderOBB& getOBBCollider() { return colliderOBB; };

	void incrementAcceleration(NMath::Vector3 accelerate);
	NMath::Vector3  getAcceleration() const;

	void incrementVelocity(NMath::Vector3 newVel);
	NMath::Vector3  getVelocity() const { return velocity; };

private:
	NColliderAABB		collider;
	NColliderOBB		colliderOBB;

	// Function ptr that is called to perform testing.
	std::function<void(NPhysicsComponent*)>   function_ptr = nullptr;

private:
	// The Mass of the object in 3D Space.
	float			mass = 1.0f;
	NMath::Vector3  acceleration = NMath::Vector3(0.0f, 0.0f, 0.0f);
	NMath::Vector3  velocity = NMath::Vector3(0.0f, 0.0f, 0.0f);

	bool			is_kinematic = false;
};