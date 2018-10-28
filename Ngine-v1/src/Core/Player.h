// File - Player.h
// Description - A basic player class which the player will have control over.

#pragma once

#include "NGameObject.h"

class NCamera;

class NPlayer : public NGameObject 
{
public:
	NPlayer();

	void Update(GameStateData& gameData) override;
	void Render(NRenderer* renderer) override;

	void onCollision(NPhysicsComponent* component);

	void setCamera(NCamera* camera);

private:
	void updateCameraPosition(float speed, NInputHandler* input);

private:
	NCamera*   playerCamera = nullptr;
};