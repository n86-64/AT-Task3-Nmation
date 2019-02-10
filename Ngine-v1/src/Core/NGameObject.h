// File - GameObject.h
// Discription - Represents an Object within the Game Scene.

#pragma once

#include <vector>

#include "Helpers/NMaths.h"

#include "Core/NDataStructures.h"
#include "Core/InputHandler.h"
#include "Core/time.h"

#include "NColliderAABB.h"

#include "NComponent.h"

class NRenderer;

class NGameObject 
{
public:
	NGameObject() {};

	virtual void init(EngineStateData& engineSetup) {};

	// Consider adding a pre-tick and post tick.
	// TODO - Implimenting Timing values.
	// Updates the engine each frame.
	virtual void Update(GameStateData& gameData);

	// Renders the object on screen.
	// TODO - Have renderer register components then draw.
	virtual void Render(NRenderer* renderer);

	NMath::Vector3  getPosition();
	void		    setPosition(NMath::Vector3 newPos);
	NMath::Vector3  getRotation();
	void			setRotation(NMath::Vector3  newRot);
	NMath::Vector3  getScale();
	void			setScale(NMath::Vector3 newScale);

	// Add a component to the list.
	void addComponent(NComponent* newComp);

	// DEPRICATED!!!!
	NMath::Vector3   getTransformValue();

	NComponent*			getComponent(int i);
	int					getComponentCount(); 

	DirectX::XMMATRIX   getModelMatrix();

	template<class T>
	T* getComponentByType();

protected:
	std::vector<std::unique_ptr<NComponent>> objectComponents;

	/* 3D Object Transforms. (Allows us to render these objects.) */
	NMath::Vector3  position; // The position of the object in 3D space. 
	NMath::Vector3	rotation; // The rotation of the object (represented via quaternions.)
	NMath::Vector3  scale = NMath::Vector3(1.0f, 1.0f, 1.0f); // The scale of the object in 3D space. (By Default Set to 1)

protected:
	// Object Directions.
	const NMath::Vector3  forward = NMath::Vector3(0.0f, 0.0f, 1.0f);
	const NMath::Vector3  right   = NMath::Vector3(1.0f, 0.0f, 0.0f);
	const NMath::Vector3  up      = NMath::Vector3(0.0f, 1.0f, 0.0f);
};

template<class T>
inline T * NGameObject::getComponentByType()
{
	for (int i = 0; i < objectComponents.size(); i++) 
	{
		if (dynamic_cast<T*>(objectComponents[i].get())) 
		{
			return (T*)objectComponents[i].get();
		}
	}
}
