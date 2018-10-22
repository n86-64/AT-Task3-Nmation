// File - Player.h
// Description - A basic player class which the player will have control over.

#pragma once

#include "NGameObject.h"

class NPlayer : public NGameObject 
{
public:
	NPlayer();

	void Update(GameStateData& gameData) override;
	void Render(NRenderer* renderer) override;

	void onCollision(NPhysicsComponent* component);

private:

};