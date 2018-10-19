#pragma once


#include <vector>

// The NGame class will go here.
#include "Core/NWinEvent.h"
#include "Renderer/NRenderer.h"
#include "Helpers/Platform.h"
#include "NGameObject.h"
#include "InputHandler.h"
#include "time.h"
#include "SceneManager.h"

class NGame 
{
public:
	NGame() {};

	// Deprecated - do not use.
	void init(NWindowHandle* window, std::string gameTitle); // Initialises the Engine.  

	// Initialises the engine.
	bool init(NWindowHandle* window, NInitSettings launchParams);

	// Update routienes
	void Tick();
	void Update();
	void Render();

	// Retreive Window events from Windowing systems. 
	void ProcessWindowEvents(NWinEvent winEvent);

	bool shouldQuit() const;

private:
	// Here we will store the games components.
	NWindow				gameWindow;
	NRenderer			renderer;
	NInputHandler		input;
	NTimer				gameTime;
	GameStateData		gameData = { &gameTime, &input };

	NScene				gameSceneManager; 


	// Temporary Scene Manager - TODO: Build a scene manager
	std::vector<std::unique_ptr<NGameObject>>	scene_objects;

	void ShutDown();
	bool quit = false;

	float timetest = 0.0f;
};