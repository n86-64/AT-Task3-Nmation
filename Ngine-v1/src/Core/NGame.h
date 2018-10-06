#pragma once

// The NGame class will go here.

#include "Core/NWinEvent.h"
#include "Renderer/NRenderer.h"
#include "Helpers/Platform.h"

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

	// Retreive Window events from Windowing systems. 
	void ProcessWindowEvents(NWinEvent winEvent);

	bool shouldQuit() const;

private:
	// Here we will store the games components.
	NWindow     gameWindow;
	NRenderer   renderer;

	void ShutDown();
	bool quit = false;
};