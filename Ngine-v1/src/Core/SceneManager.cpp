#include "Renderer/NRenderer.h"

// Individual components for setup.
#include "NPhysicsComponent.h"

#include "Camera.h"
#include "SceneManager.h"

bool NScene::init(NRenderer* renderer, GameStateData* gameState)
{
	gameStateData = gameState;
	gameRenderer = renderer;
	return true;
}

void NScene::Update()
{
	physicsSystem.tickPhysics(*gameStateData);

	for (int i = 0; i < scene_objects.size(); ++i)
	{
		// Update the objects.
		scene_objects[i]->Update(*gameStateData);
	}
}

void NScene::Render()
{
	for (int i = 0; i < scene_objects.size(); ++i)
	{
		// Update the objects.
		scene_objects[i]->Render(gameRenderer);
	}
}

void NScene::addObjectToScene(NGameObject* newObject)
{
	if (dynamic_cast<NCamera*>(newObject)) 
	{
		gameRenderer->setMainCamera((NCamera*)newObject);
	}

	// Here we will add objects to the scene/scene-manager. 
	NComponent* component = nullptr;
	for (int i = 0; i < newObject->getComponentCount(); i++) 
	{
		component = newObject->getComponent(i);

		// Here we can set up each component individually. 
		if (dynamic_cast<NPhysicsComponent*>(component)) 
		{
			physicsSystem.RegisterObject(((NPhysicsComponent*)component));
		}
	}

	// Here we will perform some object setup. 
	scene_objects.push_back(std::unique_ptr<NGameObject>(newObject));
}
