// NAnimationComponent.h
// Discription - Manages animations for the selectd skeleton.


#pragma once

#include "NComponent.h"

class NAnimation;

class NAnimationComponent : public NComponent 
{
public:
	NAnimationComponent() = default;


	// Inherited via NComponent
	virtual void Construct(EngineStateData engineState, NConstructorValues constructorData) override;
	virtual void Update(GameStateData & gameData) override;
	virtual void Render(NRenderer * renderer) override;

	void setAnimation(NAnimation* newAnim); 
	bool hasAnimation() { return (selectedAnimation != nullptr); }


private:
	NAnimation* selectedAnimation = nullptr;

};