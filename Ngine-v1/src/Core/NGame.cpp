#include <string>
#include "NGame.h"


// Game Objects to put in the scene.
#include "Camera.h"

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

#pragma region TEST_SCENE_SETUP
	// Here we set up a basic test scene.
	scene_objects.push_back(std::make_unique<NCamera>());
	renderer.setMainCamera((NCamera*)scene_objects[0].get());
#pragma endregion


	return true;
}

void NGame::Tick()
{
	Update();
	Render();
}

void NGame::Update()
{
	for (int i = 0; i < scene_objects.size(); ++i) 
	{
		// Update the objects.
		scene_objects[i]->Update();
	}
}

void NGame::Render()
{
	renderer.Clear(); // Clear the screen with a render target of some form.

	// TODO - Add code to render the child objects.
	for (int i = 0; i < scene_objects.size(); ++i)
	{
		// Update the objects.
		scene_objects[i]->Render(&renderer);
	}

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
