#include "Renderer/NRenderer.h"

#include "SceneManager.h"

bool NScene::init(NRenderer* renderer, GameStateData* gameState)
{
	gameStateData = gameState;
	gameRenderer = gameRenderer;
	return true;
}

void NScene::Update()
{
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
	// Here we will add objects to the scene/scene-manager. 

	// Here we will perform some object setup. 
	scene_objects.push_back(std::unique_ptr<NGameObject>(newObject));
}
