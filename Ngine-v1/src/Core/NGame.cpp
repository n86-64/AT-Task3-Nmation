#include <string>
#include "NGame.h"

// Includes the game objects for the test scene.
#include "Camera.h"
#include "Triangle.h"
#include "Player.h"

#include "NPhysicsComponent.h"
#include "N3DComponent.h"

// DEPRECATED
void NGame::init(NWindowHandle* window, std::string gameTitle)
{
	gameWindow.setAndSetupNWindow(window);
	gameWindow.setWindowTitle(gameTitle);
}

bool NGame::init(NWindowHandle* window, NInitSettings launchParams)
{
	bool initialised = false;
	gameWindow.setAndSetupWindow(window, launchParams.nCmdShow);
	gameWindow.setWindowTitle(launchParams.gameTitle);

	NRendererConfig initParams = {};
	initParams.width = 1280;
	initParams.height = 720;

	gameWindow.setWindowSize(initParams.width, initParams.height); // Set the window rectangle to match the resolution.
	
	initialised = renderer.init(*gameWindow.getWindowHandle(), initParams);
	initialised = gameSceneManager.init(&renderer, &gameData);

	if (!initialised)
	{
		ShutDown();
	}

#pragma region TEST_SCENE_SETUP
	// Here we set up a basic test scene. (Will be deprecated)
	NCamera* newCam = new NCamera();

	NMaterial* testMat = renderer.createMaterial("test");
	NMaterial* testMat2 = renderer.createMaterial("test");

	Triangle* testTriangle = new Triangle(testMat);
	Triangle* testTriangle2 = new Triangle(testMat2);

	N3DComponent* comp = new N3DComponent();
	comp->setGameObject(testTriangle);
	comp->setMaterial(renderer.createMaterial("test"));
	comp->setMesh(renderer.createMesh("cube"));
	testTriangle->addComponent(comp);

	N3DComponent* comp2 = new N3DComponent();
	comp2->setGameObject(testTriangle2);
	comp2->setMaterial(renderer.createMaterial("test"));
	comp2->setMesh(renderer.createMesh("bunny"));
	testTriangle2->addComponent(comp2);

	NPhysicsComponent*  physComp = new NPhysicsComponent();
	physComp->registerCollisionEvent(std::bind(&Triangle::colTest, testTriangle, std::placeholders::_1));
	physComp->setGameObject(testTriangle);
	physComp->isKinematic(true);
	physComp->getCollider().setColliderDimenstions(NMath::Vector3(10.0f, 1.0f, 10.0f));
	physComp->getOBBCollider().setSize(NMath::Vector3(10.0f, 1.0f, 10.0f));
	testTriangle->addComponent(physComp);

	NPlayer* player = new NPlayer();
	N3DComponent* playerMesh = new N3DComponent();
	playerMesh->setMesh(renderer.createMesh("cube"));
	playerMesh->setMaterial(renderer.createMaterial("test"));
	player->addComponent(playerMesh);
	player->setCamera(newCam);
	newCam->setPosition(NMath::Vector3(5.0f, 10.0f, -5.0f));
	player->setScale(NMath::Vector3(1.0f, 1.0f, 1.0f));

	testTriangle->setPosition(NMath::Vector3(0.0f, 0.0f, 0.0f));
	testTriangle->setScale(NMath::Vector3(10.0f, 1.0f, 10.0f));
	//testTriangle2->setPosition(NMath::Ve ctor3(3.0f, 0.0f, 0.0f));
	player->setPosition(NMath::Vector3(0.0f, 20.0f, 0.0f));
	//player->setRotation(NMath::Vector3(0.0f, 90.0f, 0.0f));

	gameSceneManager.addObjectToScene(testTriangle);
//	gameSceneManager.addObjectToScene(testTriangle2);
	gameSceneManager.addObjectToScene(newCam);
	gameSceneManager.addObjectToScene(player);

#pragma endregion

	return initialised;
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
	gameSceneManager.Update();

	// TEMPORARY, do not keep
	if (input.getKeyDown(KEY_ESCAPE)) 
	{
		quit = true;
	}
}

void NGame::Render()
{
	renderer.Clear(); // Clear the screen with a render target of some form.
	gameSceneManager.Render();
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
}
