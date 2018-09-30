#include <string>
#include "NGame.h"

// DEPRECATED
void NGame::init(NWindowHandle* window, std::string gameTitle)
{
	gameWindow.setAndSetupNWindow(window);
	gameWindow.setWindowTitle(gameTitle);
}

bool NGame::init(NWindowHandle* window, NInitSettings launchParams)
{
	gameWindow.setAndSetupWindow(window, launchParams.nCmdShow);
	gameWindow.setWindowTitle(launchParams.gameTitle);

	NRendererConfig initParams = {};
	initParams.width = 1280;
	initParams.height = 720;

	gameWindow.setWindowSize(initParams.width, initParams.height); // Set the window rectangle to match the resolution.
	
	if (!renderer.init(*gameWindow.getWindowHandle(), initParams)) 
	{
		ShutDown();
		return false;
	}

	return true;
}

void NGame::Update()
{
	renderer.Clear(); // Clear the screen with a render target of some form.

	// TODO - Add code to render the child objects.

	// TEST ONLY - Get a Triangle Drawing.

	renderer.Present(); // Render the images.
}

void NGame::ProcessWindowEvents(NWinEvent winEvent)
{
	NWindowMessage message = winEvent.getEventData();

	switch (message.message) 
	{
	case WM_DESTROY:
		ShutDown();
		quit = true;
		break;
	case WM_SIZE:
		OutputDebugString("The window has been resized \n");
		break;
	}
}

bool NGame::shouldQuit() const
{
	return quit;
}

void NGame::ShutDown()
{
	// Clean up the engine and then terminate cleanly.
	gameWindow.CloseWindow();
}
