// File - NPhysicsComponent.h
// Description - A component used to perform physics calculations.

#pragma once

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

private:
	NColliderAABB		collider;

	// TODO - Consider Collider parent class so a veriaty of collisions can be simulated. 
};