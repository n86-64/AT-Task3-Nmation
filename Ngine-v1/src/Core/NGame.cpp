#include <string>
#include "NGame.h"

void NGame::init(NWindowHandle* window, std::string gameTitle)
{
	gameWindow.setAndSetupNWindow(window);
	gameWindow.setWindowTitle(gameTitle);
}

bool NGame::init(NWindowHandle * window, NInitSettings launchParams)
{
	gameWindow.setAndSetupWindow(window, launchParams.nCmdShow);
	gameWindow.setWindowTitle(launchParams.gameTitle);

	NRendererInit initParams = {};
	initParams.width = 800;
	initParams.height = 600;

	gameWindow.setWindowSize(initParams.width, initParams.height); // Set the window rectangle to match the resolution.
	renderer.init(*gameWindow.getWindowHandle(), initParams);

	return true;
}

void NGame::ProcessWindowEvents(NWinEvent winEvent)
{
	NWindowMessage message = winEvent.getEventData();

	switch (message.message) 
	{
	case WM_DESTROY:
		ShutDown();
		break;
	case WM_SIZE:
		OutputDebugString("The window has been resized");
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
	quit = true;
}
