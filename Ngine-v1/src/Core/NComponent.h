// File - NComponent.h
// Description - Defines a component which provides a fundemental behaviour to objects.

#pragma once

#include "NDataStructures.h"

class NGameObject;

class NComponent 
{
public:
	// Default constructor and destructor.
	NComponent() = default;
	virtual ~NComponent() = default;

	// The constructor for the 
	virtual void Construct(EngineStateData engineState, NConstructorValues constructorData) = 0;

	// Update and render the components.
	virtual void Update() = 0;
	virtual void Render(NRenderer* renderer) = 0;

	NGameObject* getGameObject();
	void		 setGameObject(NGameObject* obj);

protected:
	NGameObject* parentObject = nullptr;
};
