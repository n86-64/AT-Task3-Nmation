#include <string>
#include "NGame.h"

// Includes the game objects for the test scene.
#include "Camera.h"
#include "Triangle.h"
#include "TestComp.h"

#include "N3DComponent.h"

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

	NMaterial* testMat = renderer.createMaterial("test");
	NMaterial* testMat2 = renderer.createMaterial("test");

	Triangle* testTriangle = new Triangle(testMat);
	Triangle* testTriangle2 = new Triangle(testMat2);
	testTriangle->addComponent(new TestComp());

	N3DComponent* comp = new N3DComponent();
	comp->setGameObject(testTriangle);
	comp->setMaterial(renderer.createMaterial("test"));
	comp->setMesh(renderer.createMesh("bunny"));
	testTriangle->addComponent(comp);

	N3DComponent* comp2 = new N3DComponent();
	comp2->setGameObject(testTriangle2);
	comp2->setMaterial(renderer.createMaterial("test"));
	comp2->setMesh(renderer.createMesh("bunny"));
	testTriangle->addComponent(comp2);

	testTriangle->setPosition(NMath::Vector3(0.0f, 0.0f, 0.0f));
	testTriangle2->setPosition(NMath::Vector3(1.0f, 2.0f, 0.0f));

	scene_objects.push_back(std::unique_ptr<Triangle>(testTriangle));
	scene_objects.push_back(std::unique_ptr<Triangle>(testTriangle2));// TODO - Have scene manager automagiclly get renderer to setup drawables. 
#pragma endregion

	return true;
}

void NGame::Tick()
{
	gameTime.tick();

	Update();
	Render();
	input.updateStates();

	// If quit is true we shutdown before exiting.
	if (quit) 
	{
		ShutDown(); 
	}
}

void NGame::Update()
{
	float test = gameTime.getDeltaTime();
	std::string testString = std::to_string(test) + "\n";
	OutputDebugString(testString.c_str());
	
	for (int i = 0; i < scene_objects.size(); ++i) 
	{
		// Update the objects.
		scene_objects[i]->Update(gameData);
	}

	//if (timetest >= 5000.0f) 
	//{
	//	quit = true;
	//}

	// TEMPORARY, do not keep
	if (input.getKeyDown(KEY_ESCAPE)) 
	{
		quit = true;
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
	case WM_INPUT:
	case WM_MOUSEMOVE:
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_MBUTTONDOWN:
	case WM_MBUTTONUP:
	case WM_MOUSEWHEEL:
	case WM_XBUTTONDOWN:
	case WM_XBUTTONUP:
	case WM_MOUSEHOVER:
		input.updateMouseState(winEvent);
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
