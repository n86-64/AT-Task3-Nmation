#pragma once

// The NGame class will go here.
#include "Core/NWinEvent.h"
#include "Helpers/Win32Ref.h"

class NGame 
{
public:
	NGame() {};

	void init(HWND* window, std::string gameTitle); // Initialises the Engine. 

	// Retreive WinProc Events. 
	void ProcessWindowEvents(NWinEvent winEvent);

private:
	// Here we will store the games components.
};