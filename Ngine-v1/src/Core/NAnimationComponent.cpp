#include "NAnimationComponent.h"

void NAnimationComponent::Construct(EngineStateData engineState, NConstructorValues constructorData)
{
}

void NAnimationComponent::Update(GameStateData & gameData)
{
	// Track the time and ensure the correct data is moved. 

}

void NAnimationComponent::Render(NRenderer * renderer)
{

}

void NAnimationComponent::setAnimation(NAnimation* newAnim)
{
	selectedAnimation = newAnim;
}
