// File - TestComponent.h
// Description - A component to test out rendering components.


#pragma once

#include "NComponent.h"

class TestComp : public NComponent
{
public:
	TestComp() = default;

	// Inherited via NComponent
	virtual void Construct(EngineStateData engineState, NConstructorValues constructorData) override;
	virtual void Update() override;
	virtual void Render(NRenderer * renderer) override;
};