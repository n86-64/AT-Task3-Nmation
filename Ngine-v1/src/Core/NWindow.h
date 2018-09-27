#pragma once

// NWindow class will go here.

#include <functional>
#include <string>
#include <tchar.h>

#include "Helpers/Platform.h"

// Represents the window object.
// ONLY the window though, events are processed seperatly.
class NWindow 
{
public:
	NWindow();
	NWindow(NWindowHandle* window);

	void setAndSetupNWindow(NWindowHandle* window);

	// Window properties will be shown here.
	void setWindowTitle(std::string newWindowTitle);

	NWindowHandle* getWindowHandle();

	void updateWindow(); // Retrieves messages from the window. 

private:
	NWindowHandle* windowObject;
};