#include <string>
#include "NGame.h"

// Includes the game objects for the test scene.
#include "Camera.h"
#include "Triangle.h"

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
	// Here we set up a basic test scene. (Will be deprecated)
	scene_objects.push_back(std::make_unique<NCamera>());
	renderer.setMainCamera((NCamera*)scene_objects[0].get());

	NMaterial* testMat = renderer.createMaterial("Test");
	Triangle* testTriangle = new Triangle(testMat);

	if (!renderer.setupTriangle(testTriangle)) 
	{
		ShutDown();
		return false;
	}

	scene_objects.push_back(std::unique_ptr<Triangle>(testTriangle)); // TODO - Have scene manager automagiclly get renderer to setup drawables. 
#pragma endregion


	return true;
}

void NGame::Tick()
{
	Update();
	Render();
	input.resetStates();
}

void NGame::Update()
{
	for (int i = 0; i < scene_objects.size(); ++i) 
	{
		// Update the objects.
		scene_objects[i]->Update(&input);
	}

	if (input.getKeyDown(NKeyboardKeys::KEY_A)) 
	{
		OutputDebugString("LOL keys down \n");
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
	case WM_KEYDOWN:
	case WM_KEYUP:
	case WM_SYSKEYUP:
	case WM_SYSKEYDOWN:
		input.updateKeyboardState(winEvent);
		break;
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
	scene_objects.clear();
}
