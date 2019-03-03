#include "time.h"
#include "NAnimation.h"
#include "NSkeletalMeshComponent.h"
#include "NAnimationComponent.h"

void NAnimationComponent::Construct(EngineStateData engineState, NConstructorValues constructorData)
{
}

void NAnimationComponent::Update(GameStateData & gameData)
{
	if (selectedAnimation) 
	{
		// Track the time and ensure the correct data is moved. 
		elapsedTicks += gameData.timeData->getDeltaTimeInSeconds() / selectedAnimation->getTickrate();
	}
}

void NAnimationComponent::Render(NRenderer * renderer)
{

}

void NAnimationComponent::setAnimation(NAnimation* newAnim)
{
	selectedAnimation = newAnim;
}

void NAnimationComponent::updateBoneData(NSkeletalMeshComponent* skeletalMeshComp)
{
	DirectX::XMMATRIX   nodeTransform = DirectX::XMMatrixIdentity();
	NSkeletalMesh* mesh = skeletalMeshComp->getMesh();

	// We have an animation so go throgh each node and update the bone position based on interpolation.
	for (int i = 0; i < selectedAnimation->getAnimCount(); i++) 
	{

	}
}
