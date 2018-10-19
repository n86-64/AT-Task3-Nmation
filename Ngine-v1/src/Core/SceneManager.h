// File - SceneManager.h
// Description - Defines a scene manager which manages information in the scenes.

#pragma once

#include "NGameObject.h"

struct GameStateData;
class NRenderer;

// TODO - Add a system for capturing events.

class NScene
{
public:
	NScene() = default;

	// Initialise the scene manager.
	bool init(NRenderer* renderer, GameStateData*  gameState);

	void Update();
	void Render();

	void addObjectToScene(NGameObject* newObject);

private:

	// scene management objects.
	std::vector<std::unique_ptr<NGameObject>>	scene_objects;
	GameStateData*								gameStateData = nullptr;
	NRenderer*									gameRenderer = nullptr;
};