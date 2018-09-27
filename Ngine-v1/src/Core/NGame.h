#pragma once

// The NGame class will go here.

#include "Core/NWinEvent.h"
#include "Core/NWindow.h"
#include "Helpers/Platform.h"

class NGame 
{
public:
	NGame() {};

	// Deprecated - do not use.
	void init(NWindowHandle* window, std::string gameTitle); // Initialises the Engine.  

	// Initialises the engine.
	void init(NWindowHandle* window, NInitSettings launchParams);

	// Retreive Window events from Windowing systems. 
	void ProcessWindowEvents(NWinEvent winEvent);

private:
	// Here we will store the games components.
	NWindow  gameWindow;
};