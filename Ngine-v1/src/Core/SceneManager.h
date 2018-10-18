// File - SceneManager.h
// Description - Defines a scene manager which manages information in the scenes.

#pragma once


class GameStateData;
class NRenderer;

class NScene
{
public:
	NScene();

	// Initialise the scene manager.
	bool init();

	void Update();
	void Render();
};