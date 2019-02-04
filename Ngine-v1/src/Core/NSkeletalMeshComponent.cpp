#include "Renderer/NRenderer.h"
#include "NSkeletalMeshComponent.h"

NMaterial * NSkeletalMeshComponent::getMaterial()
{
	return material;
}

void NSkeletalMeshComponent::setMaterial(NMaterial * newMaterial)
{
	material = newMaterial;
}

void NSkeletalMeshComponent::Construct(EngineStateData engineState, NConstructorValues constructorData)
{
}

void NSkeletalMeshComponent::Update(GameStateData& gameData)
{
	return;
}

void NSkeletalMeshComponent::Render(NRenderer* renderer)
{
	renderer->DrawObject(this);
}
