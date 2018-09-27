#pragma once

// The NGame class will go here.

#include "Core/NWinEvent.h"
#include "Helpers/Platform.h"

class NGame 
{
public:
	NGame() {};

	void init(NWindowHandle* window, std::string gameTitle); // Initialises the Engine. 

	// Retreive Window events from Windowing systems. 
	void ProcessWindowEvents(NWinEvent winEvent);

private:
	// Here we will store the games components.
};